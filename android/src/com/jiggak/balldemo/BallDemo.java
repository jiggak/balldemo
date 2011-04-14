package com.jiggak.balldemo;

import java.io.IOException;
import java.io.InputStream;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;
import android.view.Display;
import android.view.MotionEvent;
import android.view.Window;
import android.view.WindowManager;

public class BallDemo extends Activity {
   private static final String LOGTAG = "balldemo";

   static {
      System.loadLibrary("balldemo");
   }

   public native void nativeOnCreate(int width, int height);
   public native void nativeOnDestroy();
   
   public static native void load();
   public static native void drawFrame();
   public static native void touchUp(int x, int y);

   private GLSurfaceView view;
   
   public static void logInfo(String fmt, Object... args) {
      Log.i(LOGTAG, String.format(fmt, args));
   }
   
   public static void logError(Exception e, String fmt, Object... args) {
      Log.e(LOGTAG, String.format(fmt, args), e);
   }
   
   public static void logError(String fmt, Object... args) {
      Log.e(LOGTAG, String.format(fmt, args));
   }

   @Override
   public void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);

      requestWindowFeature(Window.FEATURE_NO_TITLE);

      getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
            WindowManager.LayoutParams.FLAG_FULLSCREEN);

      Display display = getWindowManager().getDefaultDisplay();
      int width = display.getWidth();
      int height = display.getHeight();

      // create engine in native code
      nativeOnCreate(width, height);

      setContentView(view = new SurfaceView(getApplication()));
   }

   public byte[] loadResource(String path) {
       logInfo("loadResource(%s)", path);
       
       InputStream in = null;
       
       try {
          in = getAssets().open(path);
          
          int size = in.available();
          byte[] buffer = new byte[size];
          
          if (in.read(buffer) != size) {
             logError("loadResource() short read %d != %d", buffer.length, size);
          }
          
          return buffer;
       } catch (IOException e) {
          logError(e, "loadResource() failed");
       } finally {
          try { in.close(); }
          catch (IOException e) { }
       }
       
       return null;
    }

   @Override
   protected void onPause() {
      super.onPause();
      view.onPause();
   }

   @Override
   protected void onResume() {
      super.onResume();
      view.onResume();
   }
   
   @Override
   protected void onDestroy() {
      super.onDestroy();
      nativeOnDestroy();
   }
}

class SurfaceView extends GLSurfaceView {
   private SurfaceViewRenderer renderer;

   public SurfaceView(Context context) {
      super(context);
      
      // need translucent since textures have alpha channel
      getHolder().setFormat(PixelFormat.TRANSLUCENT);

      setEGLContextFactory(new GLSurfaceView.EGLContextFactory() {
         public EGLContext createContext(EGL10 egl, EGLDisplay display, EGLConfig eglConfig) {
            final int EGL_CONTEXT_CLIENT_VERSION = 0x3098;

            EGLContext context = egl.eglCreateContext(
                  display,
                  eglConfig,
                  EGL10.EGL_NO_CONTEXT,
                  new int[] { EGL_CONTEXT_CLIENT_VERSION, 2, EGL10.EGL_NONE }
            );

            return context;
         }

         public void destroyContext(EGL10 egl, EGLDisplay display, EGLContext context) {
            egl.eglDestroyContext(display, context);
         }
      });

      setEGLConfigChooser(new GLSurfaceView.EGLConfigChooser() {
         public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display) {
            final int EGL_OPENGL_ES2_BIT = 4;

            int[] configAttribs = {
                  EGL10.EGL_RED_SIZE, 4,
                  EGL10.EGL_GREEN_SIZE, 4,
                  EGL10.EGL_BLUE_SIZE, 4,
                  EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                  EGL10.EGL_NONE
            };

            int[] num_config = new int[1];
            egl.eglChooseConfig(display, configAttribs, null, 0, num_config);

            int numConfigs = num_config[0];
            if (numConfigs <= 0) {
               throw new IllegalArgumentException("No configs match configSpec");
            }

            EGLConfig[] configs = new EGLConfig[numConfigs];
            egl.eglChooseConfig(display, configAttribs, configs, numConfigs, num_config);

            return chooseConfig(egl, display, configs);
         }

         public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display, EGLConfig[] configs) {
            for (EGLConfig config : configs) {
               int r = findConfigAttrib(egl, display, config, EGL10.EGL_RED_SIZE, 0);
               int g = findConfigAttrib(egl, display, config, EGL10.EGL_GREEN_SIZE, 0);
               int b = findConfigAttrib(egl, display, config, EGL10.EGL_BLUE_SIZE, 0);
               int a = findConfigAttrib(egl, display, config, EGL10.EGL_ALPHA_SIZE, 0);

               // only really care about 8bit rgba
               if (r == 8 && g == 8 && b == 8 && a == 8)
                  return config;
            }

            return null;
         }

         private int findConfigAttrib(EGL10 egl, EGLDisplay display, EGLConfig config, int attribute, int defaultValue) {
            int[] value = new int[1];
            if (egl.eglGetConfigAttrib(display, config, attribute, value)) {
               return value[0];
            }
            return defaultValue;
         }
      });
      
      // create renderer that simply passes control into native code
      setRenderer(renderer = new SurfaceViewRenderer());
   }

   public boolean onTouchEvent(MotionEvent event) {
      final int x = (int) event.getX();
      final int y = (int) event.getY();

      // execute touch events on the rendering thread
      queueEvent(new Runnable() {
         public void run() {
            renderer.handleTouchUp(x, y);
         }
      });

      return false;
   }
}

class SurfaceViewRenderer implements GLSurfaceView.Renderer {
    public void onDrawFrame(GL10 gl) {
       BallDemo.drawFrame();
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) { }

    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
       BallDemo.load();
    }

    public void handleTouchUp(int x, int y) {
       BallDemo.touchUp(x, y);
    }
 }
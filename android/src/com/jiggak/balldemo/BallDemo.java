package com.jiggak.balldemo;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;

public class BallDemo extends Activity {
	static {
    	System.loadLibrary("balldemo");
    }
    
    public static native void drawFrame();
    public static native void init(int width, int height);
    
    private GLSurfaceView view;
    
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, 
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        
        view = new GLSurfaceView(getApplication());
        
        // need translucent since textures have alpha channel
        view.getHolder().setFormat(PixelFormat.TRANSLUCENT);
        
        view.setEGLContextFactory(new GLSurfaceView.EGLContextFactory() {
        	@Override
        	public EGLContext createContext(EGL10 egl, EGLDisplay display, EGLConfig eglConfig) {
        		final int EGL_CONTEXT_CLIENT_VERSION = 0x3098;
        		
        		EGLContext context = egl.eglCreateContext(display,
        				eglConfig,
        				EGL10.EGL_NO_CONTEXT,
        				new int[] {EGL_CONTEXT_CLIENT_VERSION, 2, EGL10.EGL_NONE}
        		);
        		
        		return context;
        	}
        	
        	@Override
        	public void destroyContext(EGL10 egl, EGLDisplay display, EGLContext context) {
        		egl.eglDestroyContext(display, context);
        	}
        });
        
        view.setEGLConfigChooser(new GLSurfaceView.EGLConfigChooser() {
			@Override
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
				for(EGLConfig config : configs) {
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
				int [] value = new int[1];
	            if (egl.eglGetConfigAttrib(display, config, attribute, value)) {
	                return value[0];
	            }
	            return defaultValue;
	        }
		});
        
        // create renderer that simply passes control into native code
        view.setRenderer(new GLSurfaceView.Renderer() {
        	@Override
        	public void onDrawFrame(GL10 gl) {
        		drawFrame();
        	}
        	
        	@Override
        	public void onSurfaceChanged(GL10 gl, int width, int height) {
        		init(width, height);
        	}
        	
        	@Override
        	public void onSurfaceCreated(GL10 gl, EGLConfig config) { }
        });
        
        setContentView(view);
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
}
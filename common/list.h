/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <josh@slashdev.ca> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Josh Kropf
 * ----------------------------------------------------------------------------
 */
#ifndef LIST_H_
#define LIST_H_

///
/// Linked list template class. The list stores pointers to values. All methods
/// that remove nodes from the list require the caller to free the values.
///
template <typename T>
class list {
private:
   /// Node of the linked list.
   struct node {
      const T * value;
      node * next, * previous;

      /// Create node from value with next and previous set to NULL.
      node(const T * val) : value(val), next(0), previous(0) { }
   };

   struct node * _first, * _last;

   int _count;

public:
   /// Class for iterating over the list contents.
   class cursor {
   private:
      struct node * _node;

   public:
      cursor(struct node * n) : _node(n) { }

      /// Returns true if next() method will return another value.
      /// @see next()
      inline bool more() { return _node != 0; }

      /// Returns value at current cursor position and then advances the cursor.
      const T * next() {
         const T * retval = _node->value;
         _node = _node->next;
         return retval;
      }
   };

   list() : _first(0), _last(0), _count(0) { }

   ~list() {
      while (_first) {
         node * next = _first->next;
         delete _first;
         _first = next;
      }
   }

   /// Append element to list.
   /// @param value pointer to element to add
   void append(const T * value) {
      if (!_first) {
         _last = _first = new node(value);
      } else {
         _last->next = new node(value);
         _last->next->previous = _last;
         _last = _last->next;
      }

      _count ++;
   }

   /// Remove element from list.
   /// @param value pointer to element to remove
   /// @return true if element was found and removed
   bool remove(const T * value) {
      node * cursor = _first;

      while (cursor) {
         if (cursor->value == value) {
            if (cursor->next) {
               cursor->next->previous = cursor->previous;
            }

            if (cursor->previous) {
               cursor->previous->next = cursor->next;
            }

            if (cursor == _first) {
               _first = cursor->next;
            }

            if (cursor == _last) {
               _last = cursor->previous;
            }

            delete cursor;
            _count --;

            return true;
         }

         cursor = cursor->next;
      }

      return false;
   }

   /// Remove element from front of the list and return the result.
   /// @return element removed from front of list, or NULL if list was empty
   const T * shift() {
      if (_first) {
         node * n = _first;
         const T * v = n->value;

         _first = _first->next;
         if (_first) {
            _first->previous = 0;
         }

         delete n;

         return v;
      }

      return 0;
   }

   /// Returns number of elements in the list.
   inline int count() const { return _count; }

   /// Create and return a cursor for iterating over the list.
   cursor iterate() {
      cursor c(_first);
      return c;
   }
};

#endif /* LIST_H_ */

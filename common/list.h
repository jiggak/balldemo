/*
 * list.h
 *
 *  Created on: Apr 7, 2011
 *      Author: josh
 */

#ifndef LIST_H_
#define LIST_H_

template <typename T>
class list {
private:
   struct node {
      const T * value;
      node * next;
      node * previous;

      node(const T * val) : value(val), next(0), previous(0) { }
   } * _first;

   struct node * _last;

   int _count;

public:
   list() : _first(0), _last(0), _count(0) { }

   ~list() {
      while (_first) {
         node * next = _first->next;
         delete _first;
         _first = next;
      }
   }

   void add(const T * value) {
      if (!_first) {
         _last = _first = new node(value);
      } else {
         _last->next = new node(value);
         _last->next->previous = _last;
         _last = _last->next;
      }

      _count ++;
   }

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

            return true;
         }

         cursor = cursor->next;
      }

      return false;
   }

   int count() const {
      return _count;
   }

   class cursor {
   private:
      struct node * _node;

   public:
      cursor(struct node * n) : _node(n) { }

      bool more() {
         return _node != 0;
      }

      const T * next() {
         const T * retval = _node->value;
         _node = _node->next;
         return retval;
      }
   };

   cursor iterate() {
      cursor c(_first);
      return c;
   }
};

#endif /* LIST_H_ */

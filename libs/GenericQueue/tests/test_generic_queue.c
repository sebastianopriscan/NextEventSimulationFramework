#include "../generic_queue.h"
#include <stdlib.h>

double pie = 3.14 ;
double double_pie = 6.28 ;

int main(void) {
  struct generic_queue_list* list = create_queue_list();
  if(list == NULL) 
    return -1;

  int status = generic_enqueue_element(list, &pie);
  if (!status)
    return status;
  double* result = (double *)generic_dequeue_element(list);
  if (*result != pie)
    return -1;

  if(list->head != NULL || list->tail != NULL) return -1 ;

  status = generic_enqueue_element(list, &double_pie);
  if (!status)
    return status;
  status = generic_enqueue_element(list, (void *) 3);
  if (!status)
    return status;

  result = (double *)generic_dequeue_element(list);
  if (*result != double_pie)
    return -1;
  if (list->head == NULL || list->tail == NULL || (int)(list->head->data) != 3)
    return -1;
  int result_int = (int) generic_dequeue_element(list);
  if (result_int != 3)
    return -1;

  if(list->head != NULL || list->tail != NULL) return -1 ;

  return 0;
}
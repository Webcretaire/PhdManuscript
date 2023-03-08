ptl_handle_eq_t event_queue_handle;
// ... 
int ret;
ptl_event_t event;

ret = PtlEQWait(event_queue_handle, &event);
 
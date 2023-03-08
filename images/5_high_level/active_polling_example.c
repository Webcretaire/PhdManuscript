ptl_handle_eq_t event_queue_handle;
// ... 
int ret;
ptl_event_t event;
do {
    ret = PtlEQGet(event_queue_handle, &event);
} while (ret == PTL_EQ_EMPTY);
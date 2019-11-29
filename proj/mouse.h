#include <stdbool.h>
#include <stdint.h>
#include <lcom/lcf.h>

uint16_t cpl2_revert_x(uint8_t byte);
uint16_t cpl2_revert_y(uint8_t byte);
void build_packet(struct packet * pack);
int mouse_subscribe_int(uint8_t *bit_no);
int mouse_unsubscribe_int();
void(mouse_ih)();
int (mouse_disable_data_reporting)();
int (mouse_enable_datarp)();
int (send_command)(uint8_t command);
int (write_argument)(uint8_t argument);
int (set_stream_mode)();
int (read_data)();
struct mouse_event* (mouse_event)(struct packet *pp);
void mouse_state_machine(struct mouse_event* ev_atual, uint8_t x_len, uint8_t tolerance);

/*new enum for mouse event types
LEFT_BUTTON:    0
RIGHT_BUTTON:   1
RELEASED:       2
OTHER_EVENT:    3
MOUSE_MOVEMENT: 4*/
enum mouse_event_type{
  LEFT_BUTTON, RIGHT_BUTTON, RELEASED, OTHER_EVENT, MOUSE_MOVEMENT
};

//new struct mouse_event (mouse_ev only accepted enum mouse_ev_t for type)
struct mouse_event{
  enum mouse_event_type type;
  int16_t delta_x, delta_y;
};

/*new enum for mouse states
INIT:           0
 DRAW_1st_LINE: 1
 PAUSE:         2
 DRAW_2nd_LINE: 3 */                                           
enum states {
  INIT, DRAW_1st_LINE, PAUSE, DRAW_2nd_LINE
};

extern enum states st;


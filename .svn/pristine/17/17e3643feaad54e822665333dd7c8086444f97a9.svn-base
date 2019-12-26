#include <mouse.h>
#include <lcom/lcf.h>
#include <ps2_mouse_macros.h>
#include <stdint.h>

//GLOBAL VARIABLES
int hook_id_mouse;
struct packet pack;
int byte_no = 0;
bool finish;

uint16_t cpl2_revert_x(uint8_t byte)
{
  uint16_t num = byte;
  if(BIT(4) & pack.bytes[0])
  {
    num -= 256;
    return num;
  }
  return byte;
}

uint16_t cpl2_revert_y(uint8_t byte)
{
  uint16_t num = byte;
  if(BIT(5) & pack.bytes[0])
  {
    num -= 256;
    return num;
  }
  return byte;
}

/*function to build the packet that is gonna be printed                                                  |7      |6      |5          |4          |3    |2    |1 |0    
BYTE1|Y_OVFL |X_OVFL |MSB yDELTA |MSB xDelta |1    |MB   |RB|LB   
BYTE2|                       xDELTA                              
BYTE3|                       yDELTA
*/
void build_packet(struct packet *p)
{
  pack.lb = BIT(0) & p->bytes[0];
  pack.rb = BIT(1) & p->bytes[0];
  pack.mb = BIT(2) & p->bytes[0];
  pack.x_ov = BIT(6) & p->bytes[0];
  pack.y_ov = BIT(7) & p->bytes[0];
  //It has two 9-bit2’s complementcounters to keep track of themouse’s movement in the plane (one in each direction)
  pack.delta_x = cpl2_revert_x(p->bytes[1]);
  pack.delta_y = cpl2_revert_y(p->bytes[2]);
}

int mouse_subscribe_int(uint8_t *bit_no) {
  hook_id_mouse = MOUSE_IRQ;
  *bit_no = hook_id_mouse;

  return sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_mouse);
}

int mouse_unsubscribe_int() {
  return sys_irqrmpolicy(&hook_id_mouse);

  // used to unsubscribe a previous subscription of the interrupt notification associated with the specified hook_id (new value of hook_id)
}

void(mouse_ih)() {
  uint8_t stat;
  uint8_t data;
  
  util_sys_inb(STAT_REG, &stat);
  if (stat & OBF) {
    if ((stat & (PAR_ERR | TIMEOUT | !AUX)) == 0) {
      util_sys_inb(OUT_BUF, &data);
      pack.bytes[byte_no % 3] = data;
      byte_no++;
    }
  }
}
int mouse_command(uint8_t command){
  return 0;
}

int (send_command)(uint8_t command){
  uint8_t status;
	int i;
	util_sys_inb (STAT_REG, &status);   //guarda na variavel status o valor do status register
	
	for (i = 0; i <= 100; i++){
		
		if ( (status & IBF) == 1 )		//checks the input buffer bit before 
		  util_sys_inb (STAT_REG, &status);
		else 
      break;
    // sai do loop depois de 20ms
		tickdelay(micros_to_ticks(DELAY_US));
	}
	
  //0x64 <- command
	sys_outb (KBC_CMD_REG, command);   
  return 0;  
}
int (write_argument)(uint8_t argument){
  uint8_t status = 0;
	int i;
	util_sys_inb(STAT_REG, &status);    //guarda na variavel status o valor do status register
  
	for (i = 0; i <= 100; i++){
	
		if ( (status & IBF) == 1 )
			util_sys_inb (STAT_REG, &status);
    else
      break;    
    // sai do loop depois de 20ms
		tickdelay(micros_to_ticks(DELAY_US));
	}
	//0x60 <- argument
	sys_outb(OUT_BUF, argument);
  return 0;
}
int (mouse_enable_datarp)(){
  
  uint8_t *var;
  
	var = (uint8_t*) malloc (1);     //var is now equal to a pointer that points to the allocated memory space of size 1 byte
	
  send_command(WRITE_MOUSE);    //WRITE_MOUSE commands the KBC to forward its argument to the mouse without any interpretation
  
  write_argument(ENABLE_DATA_REPORTING);
	
	util_sys_inb(OUT_BUF, var);    //var <- 0x60
	
	if (*var != ACK)      //if it's not OK
		return 1;

  return 0;
}

int (mouse_disable_data_reporting)(){

  uint8_t *var;
  
	var = (uint8_t*) malloc (1);     //var is now equal to a pointer that points to the allocated memory space of size 1 byte
	
  send_command(WRITE_MOUSE);    //WRITE_MOUSE commands the KBC to forward its argument to the mouse without any interpretation
  
  write_argument(DISABLE_DATA_REPORTING);
	
	util_sys_inb(OUT_BUF, var);    //var <- 0x60
	
	if (*var != ACK)      //if it's not OK
		return 1;

  return 0;
}

int (set_stream_mode)(){

  uint8_t *var;

  var = (uint8_t*) malloc (1);     //var is now equal to a pointer that points to the allocated memory space of size 1 byte
	
  send_command(WRITE_MOUSE);    //WRITE_MOUSE commands the KBC to forward its argument to the mouse without any interpretation
  
  write_argument(SET_DEFAULT);
	
	util_sys_inb(OUT_BUF, var);    //var <- 0x60
	
	if (*var != ACK)    //if it's not OK
		return 1;

  return 0;
}

int (read_data)(){
  uint8_t *cmd;
  uint8_t *par1;

  cmd = (uint8_t*) malloc (1);     //var is now equal to a pointer that points to the allocated memory space of size 1 byte
  par1 = (uint8_t*) malloc(1);     //par1 is now equal to a pointer that points to the allocated memory space of size 1 byte
  send_command(WRITE_MOUSE);    //WRITE_MOUSE commands the KBC to forward its argument to the mouse without any interpretation
  write_argument(READ_DATA);
  util_sys_inb(OUT_BUF,cmd);
  if (*cmd != ACK)    //if it's not OK
  {
    //send command again
    send_command(WRITE_MOUSE);    //WRITE_MOUSE commands the KBC to forward its argument to the mouse without any interpretation
  
    write_argument(READ_DATA);
    util_sys_inb(OUT_BUF,cmd);
    if(*cmd != ACK)
      return 1;
  }

  return 0;
}

struct mouse_event* mouse_event(struct packet *pp){
  //we need to compare with the event before to know if we are changing the event i.e. if the event before is RELEASED, we won't release the button agains because they are already released
  static struct mouse_event ev_before;
  static struct mouse_event ev_atual;
  //when the left button is pressed
  if((ev_before.type != LEFT_BUTTON) && (                                                 pp->rb == 0) && (pp->lb == 1)  && (pp->mb == 0)){
    ev_atual.type = LEFT_BUTTON;                                                 
  }                                                 
  //right button released = left button r                                                 eleased
  else if((ev_before.type != RELEASED) && (pp->rb == 0) && (pp->lb == 0)  && (pp->mb == 0)){
    ev_atual.type = RELEASED;
  }
  //when the right button is pressed
  else if((ev_before.type != RIGHT_BUTTON) && (pp->rb == 1) && (pp->lb == 0)  && (pp->mb == 0)){
    ev_atual.type = RIGHT_BUTTON; 
  }
  //middle button pressed or 2 buttons pressed
  else if((ev_before.type != OTHER_EVENT) && ((pp->rb == 1 && pp->lb == 1)||(pp->mb == 1))){
    ev_atual.type = OTHER_EVENT;
  }
  //when we move the mouse (doesn't matter wich button is pressed)
  else{
    ev_atual.type = MOUSE_MOVEMENT;
    ev_atual.delta_x = pp->delta_x;
    ev_atual.delta_y = pp->delta_y;
  }
  //update the event before
  ev_before = ev_atual;
  return &ev_atual;
  }

void mouse_state_machine(struct mouse_event* ev_atual,uint8_t x_len, uint8_t tolerance)
{ 
  enum mouse_event_type type = ev_atual->type;
  int16_t delta_x = ev_atual->delta_x, delta_y = ev_atual->delta_y;
  static int x_mov, y_mov;
  x_mov += delta_x;
  y_mov += delta_y;
  // x_mov and y_mov are variables that will change while the state is the same. they will go back to 0 if we change the state. purpose: slope and to compare with x_len

  static enum states st = INIT;
  switch(st){
    case INIT:
      printf("State: INIT \n");
      if (type == LEFT_BUTTON){
        //if the left button is pressed, we are drawing the first line
        st = DRAW_1st_LINE;
        //changes state
        x_mov = 0;
        y_mov = 0;
      } 
      break;

    case DRAW_1st_LINE:
      printf("State: DRAW_1st_LINE \n");
      if(type == MOUSE_MOVEMENT){
        //if there is mouve movement(no buttons pressed, only movement), we keep in the same state, increasing x_mov and y_mov
        /*
        x_mov += delta_x;
        y_mov += delta_y;
        */
        st = DRAW_1st_LINE;

        //the first line should be upwards, therefore all movements reported by the mouse should, in principle, have non-negative displacements along both the x and the y directions. But your algorithm must allow "small" negative displacements along both the x and the y directions, i.e. their absolute value cannot be larger than the second argument, tolerance.
        if(((delta_x < 0) || (delta_y < 0)) && (!((delta_x < 0) || (delta_y < 0))) && ((abs(delta_x)>tolerance) || (abs(delta_y) > tolerance))) st = INIT;
      }
      //all buttons not pressed
      else if(type == RELEASED){
        //The absolute value of the slope of each line must be larger than 1 and the value of the displacement of each line along the x-direction must have the minimum value specified in the first argument, x_len.
        /*
        x_mov += delta_x;
        y_mov += delta_y;
        */
        printf("xmov: %d xlen: %d ymov: %d", x_mov, x_len, y_mov);
        if((abs(y_mov) > abs(x_mov)) && (x_mov >= x_len)){
          //end of the first line
          st = PAUSE;
          //changes state
          x_mov = 0;
          y_mov = 0;
        }
        else st = INIT;
      }
      break;

    case PAUSE:
      printf("State: PAUSE \n");
      if(type == MOUSE_MOVEMENT){
        
        //if there is mouve movement(no buttons pressed, only movement), we keep in the same state, increasing x_mov and y_mov
        /*
        x_mov += delta_x;
        y_mov += delta_y;
        */
        if( y_mov > tolerance || x_mov > tolerance)
          st = INIT;

      }
      
      else if(type == RIGHT_BUTTON){
        //if the right button is pressed, we are drawing the second line
        st = DRAW_2nd_LINE;
        //changes state
        x_mov = 0;
        y_mov = 0;
      } 

      else if (type == LEFT_BUTTON){
        //if the left button is pressed, we are drawing the first line
        st = INIT;
        //changes state
        x_mov = 0;
        y_mov = 0;
      }

      break;

    case DRAW_2nd_LINE:
      /*
      x_mov += delta_x;
      y_mov += delta_y;
      */
      printf("State: DRAW_2nd_LINE \n");
      if(type == MOUSE_MOVEMENT){
        //if there is mouve movement(no buttons pressed, only movement), we keep in the same state, increasing x_mov and y_mov
        st = DRAW_2nd_LINE;
        /*
        x_mov += delta_x;
        y_mov += delta_y;
        */
        //the second line should be upwards, therefore y movements reported by the mouse should, in principle, have negative displacements along the y direction and x movements reported by the mouse should, in principle, have non-negative displacements along the x direction . But your algorithm must allow "small" negative displacements along both the x and the y directions, i.e. their absolute value cannot be larger than the second argument, tolerance.
        if((delta_x < 0) && (delta_y > 0) && (abs(delta_x)>tolerance) && (abs(delta_y) > tolerance)) st = INIT;
      } 
      //all buttons not pressed
      else if(type == RELEASED){
        //The absolute value of the slope of each line must be larger than 1 and the value of the displacement of each line along the x-direction must have the minimum value specified in the first argument, x_len.        
        if((abs(y_mov) > abs(x_mov))&& (x_mov >= x_len)){
          //changes state
          x_mov = 0;
          y_mov = 0;
          //end of the second line
          finish = true;
        }
        else st = INIT;
      }
      break;
    default:
      break;
  }
}

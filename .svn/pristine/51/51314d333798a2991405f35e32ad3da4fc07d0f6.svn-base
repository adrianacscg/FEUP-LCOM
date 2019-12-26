#include <mouse.h>
#include <lcom/lcf.h>
#include <ps2_mouse_macros.h>
#include <stdint.h>

//GLOBAL VARIABLES
int hook_id_mouse;
struct packet pack;
int byte_no = 0;

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
  if ((stat & OBF) && (stat & AUX)) {
    if ((stat & (PAR_ERR | TIMEOUT)) == 0) {
      util_sys_inb(OUT_BUF, &data);
      pack.bytes[byte_no] = data;
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


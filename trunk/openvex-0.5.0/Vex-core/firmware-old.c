/**************************************************************************
*
*   This project contains free simple code for the VEX robotics system.
*   It is provided as an aid to students, mentors, and hobbyists
*   for the purpose of programming VEX robots.
*
*   This code is based in part on the VEX default code, and Sutekh's open
*   source VEX library.  The goal of this project is to provide source
*   code for VEX robots which:
*
*   1.  Is easy to read and modify
*   2.  Provides a positive example of software engineering practices for
*       students to learn from.  This includes:
*
*       a.  Consistency in naming conventions and descriptive variable
*           and type names.
*       b.  An API (application program interface) layer between the
*           application and hardware access.  This layer hides the
*           details of hardware access, provides a forward-compatible
*           interface for new programs, and performs sanity checking.
*
*   This file should use the VEX application program interface.
*   All hardware access in this file goes through API functions such as
*   pwm_write(), io_set_digitial(), rc_read_data(), etc.  If you
*   want to code at a lower level, you shoud enhance the library
*   code in the Lib directory and create more API functions to use
*   here if necessary.
*
***************************************************************************
*
*   This code is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This code is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this code.  If not, see <http://www.gnu.org/licenses/>.
*
***************************************************************************/

#include <OpenVex.h>
#include "firmware.h"

/*************** MAIN ***************/
void    main(void)
{
    controller_init();/* This must be done first! */

    /* Initialize ports, etc. for this robot configuration. */
    custom_init();

    while (TRUE) // evaluates true every 18.5ms
    {
        if ( rc_new_data_available() )
        {
            rc_routine();
            /* Run autonomous routine when a RC upper button is pressed. */
            if ( rc_read_data(AUTONOMOUS_CHAN) == 127 )
                autonomous_routine0();
        }

        reset_buffer(&control_buffer);

        if(usart_data_available())
            serial_control();

        if ( io_read_digital(LEFT_BUMPER_PORT) == 0 )  {
            if ( io_read_digital(RIGHT_BUMPER_PORT) == 0 )
                bump_front();
            else
                bump_front_left();
        }
        else if ( io_read_digital(RIGHT_BUMPER_PORT) == 0 )
            bump_front_right();

        pwm_write(LEFT_MOTOR, LEFT_MOTOR_POWER);
        pwm_write(RIGHT_MOTOR, RIGHT_MOTOR_POWER);

        controller_submit_data(NO_WAIT);

    }
}


/*************** CUSTOM INIT ***************/
void    custom_init(void)
{
    int     c;

    /* Set some of the 16 I/O ports as inputs */
    for (c = 1; c <= 16; ++c)
        io_set_direction(c, IO_DIRECTION_IN);

    /*  Configure the number of analog input ports. Ports 1 through N will be analog, and N+1 through 16 will be digital. */
    io_set_analog_port_count(ANALOG_PORTS);

    /* Set some of the 16 I/O ports as outputs (digital output only). These can be used to drive LEDs and other low-current devices. */
    //for (c = 9; c <= 16; ++c) io_set_direction(c, IO_DIRECTION_OUT);
    /* Initialize the values on the digital outputs. */
    //for (c = 9; c <= 16; ++c) io_set_digital(c,0);
    controller_print_version();

    control_buffer.size = 0;
    control_buffer.MAX_SIZE = MAX_BUFFER_SIZE;
}

/*************** SERIAL CONTROL ***************/

void serial_control(void)
{
    putchar(ACK);
    if(usart_data_available())
    {
        switch(buffer_control_data(&control_buffer))
        {
        case 0:
            decode_op(&control_buffer);
            break;
        case NAK:
            putchar(NAK); break;
        default:
            break;
        }
    }

}


/*************** BUFFERING DATA ***************/

unsigned char buffer_control_data(struct serial_buffer *buffer) {

    unsigned char data_byte = 0;
    do
    {
        if(usart_data_available())
        {
            if((data_byte = usart_get_byte()) != ESC)
            {
                buffer->buffer[buffer->size++] = data_byte;
                switch(buffer->size)
                {
                case 'f':
                case 'b':
                case ' ':
                case '-':
                case '=':
                    data_byte = ETX;
                    break;
                }
            }
            else
            {
                return ESC;
            }
        }
    }
    while(buffer->size < buffer->MAX_SIZE && data_byte != ETX);

    return 0;
}

/*************** CLEAR THE BUFFER ***************/

void reset_buffer(struct serial_buffer *buffer)
{
    buffer->buffer[0] = 0;
    buffer->buffer[1] = 0;
    buffer->size = 0;
}

/*************** DECODE AND EXECUTE OPERATIONS ***************/
unsigned char decode_op(struct serial_buffer *buffer){

    switch(buffer->buffer[0])
    {
    case ' ':
        stop_normal(); break;
    case 'f':
        full_forward(); break;
    case 'b':
        full_backward(); break;
    case '-':
        full_left(); break;
    case '=':
        full_right(); break;
    case 'w':
    case 's':
        go_straight(buffer);  break;

    case 'l':
    case 'r':
    case 'm':
        run_motor(buffer);  break;

    case 'a':
    case 'd':
        rotate(buffer);     break;

    default:
        return ERR_BAD_DATA;
    }
    return 0;

}

/*************** GO STRAIGHT ***************/
int go_straight(struct serial_buffer *buffer){

    unsigned short i;
    signed char power;    // motor power/speed
    char mode;              // time/distance/continuous modes
    unsigned char dist_time;     // time or distance
    if(buffer->size < 3) return ERR_BAD_DATA;

    mode = buffer->buffer[1];
    power = ((signed char)buffer->buffer[2] == -128)? -127 : buffer->buffer[2];

    pwm_write(LEFT_MOTOR, power * left_motor_dir);
    pwm_write(RIGHT_MOTOR, power * right_motor_dir);
    controller_submit_data(NO_WAIT);

    if(mode != '1')
    {
        dist_time = buffer->buffer[3];
        switch(mode)
        {
        case 'm': delay_msec(dist_time); break;
        case 's': delay_sec(dist_time); break;
        case 'M': for(i=0;i<60;i++) delay_sec(dist_time); break;
        }
        pwm_write(LEFT_MOTOR, 0);
        pwm_write(RIGHT_MOTOR, 0);
        controller_submit_data(NO_WAIT);
    }

    return 0;
}

 void full_forward(void)
{
    LEFT_MOTOR_POWER = 127 * left_motor_dir;
    RIGHT_MOTOR_POWER = 127 * right_motor_dir;
}

 void full_backward(void)
{
    LEFT_MOTOR_POWER = -127 * left_motor_dir;
    RIGHT_MOTOR_POWER = -127 * right_motor_dir;

}

 void full_left(void)
{
    LEFT_MOTOR_POWER = -127 * left_motor_dir;
    RIGHT_MOTOR_POWER = 127 * right_motor_dir;
}

 void full_right(void)
{
    LEFT_MOTOR_POWER = 127 * left_motor_dir;
    RIGHT_MOTOR_POWER = -127 * right_motor_dir;
}

 void stop_normal(void)
{
    LEFT_MOTOR_POWER = 0;
    RIGHT_MOTOR_POWER = 0;
}

/*************** ROTATE ***************/
int rotate(struct serial_buffer *buffer){

    unsigned short i;
    signed char power;    // motor power/speed
    char mode;              // time/distance/continuous modes
    unsigned char angle_time;     // time or angle
    signed char left_forward = 0, right_forward = 0; // 1 = forward, -1 = backward
    if(buffer->size < 3) return ERR_BAD_DATA;

    mode = buffer->buffer[1];
    power = ((signed char)buffer->buffer[2] == -128)? -127 : buffer->buffer[2];

    switch(buffer->buffer[0])
    {
    case 'a':
        left_forward = -1;
        right_forward = 1;
        break;
    case 'd':
        left_forward = 1;
        right_forward = -1;
        break;
    }

    pwm_write(LEFT_MOTOR, power * left_motor_dir * left_forward);
    pwm_write(RIGHT_MOTOR, power * right_motor_dir * right_forward);
    controller_submit_data(NO_WAIT);

    if(mode != '1')
    {
        angle_time = buffer->buffer[3];
        switch(mode)
        {
        case 'm': delay_msec(angle_time); break;
        case 's': delay_sec(angle_time); break;
        case 'M': for(i=0;i<60;i++) delay_sec(angle_time); break;
        }
        pwm_write(LEFT_MOTOR, 0);
        pwm_write(RIGHT_MOTOR, 0);
        controller_submit_data(NO_WAIT);
    }
    return 0;
}

/*************** RUN THE MOTOR ***************/
int    run_motor(struct serial_buffer *buffer)
{
    unsigned short i;   // time counter

    signed char power;    // motor power/speed
    char mode;              // time/distance/continuous modes
    unsigned char time;     // time
    unsigned char motor_no;     // motor number
    signed char forward = 0; // 1 = forward, -1 = backward
    if(buffer->size < 3) return ERR_BAD_DATA;

    mode = buffer->buffer[1];
    power = ((signed char)buffer->buffer[2] == -128)? -127 : buffer->buffer[2];

    switch(buffer->buffer[0])
    {
    case 'l':
        motor_no = LEFT_MOTOR;
        forward = left_motor_dir;
        break;
    case 'r':
        motor_no = RIGHT_MOTOR;
        forward = left_motor_dir;
        break;
    default:
        motor_no = buffer->buffer[4];
        forward = 1;

    }

    pwm_write(motor_no, power * forward);
    controller_submit_data(NO_WAIT);

    if(mode != '1')
    {
        time = buffer->buffer[3];
        switch(mode)
        {
        case 'm': delay_msec(time); break;
        case 's': delay_sec(time); break;
        case 'M': for(i=0;i<60;i++) delay_sec(time); break;
        }
        pwm_write(LEFT_MOTOR, 0);
        pwm_write(RIGHT_MOTOR, 0);
        controller_submit_data(NO_WAIT);
    }
    return 0;
}


/*************** RC ROUTINE ***************/

void    rc_routine(void)
{
    /*
     *  Keep a count of calls to this function.  This will overflow
     *  at 2^16 (65, 536), but we don't really care since we're only
     *  interested in whether or not calls is a multiple of some number.
     */
    static unsigned int     sonar_distance = 0;
    static unsigned long    elapsed_time,
            old_time = 0;

    if ( io_read_digital(ARCADE_JUMPER_PORT) == 0 )
        arcade_drive_routine();
    else
        tank_drive_routine();

    controller_submit_data(NO_WAIT);

    elapsed_time = SYSTEM_TIMER_SECONDS();
    //printf("TIMER0 = %ld  elapsed_time = %ld  overflows = %d\n",
    //   timer0_read32(), elapsed_time, Timer0_overflows);
    if ( elapsed_time > old_time )
    {
        old_time = elapsed_time;
        #if DEBUG_STACK
                stack_report();
        #endif
        /*  Display status of various sensors and rc inputs.  */
        /*DPRINTF("ET: %ld  RC: %d %d %d %d %d %d %d  Jumper: %d\n",
                elapsed_time, rc_read_status(),
                rc_read_data(1), rc_read_data(2), rc_read_data(3), rc_read_data(4),
                rc_read_data(5), rc_read_data(6), io_read_digital(ARCADE_JUMPER_PORT)); */
    }
}

/*************** TANK DRIVE ROUTINE ***************/
void    tank_drive_routine(void)
{
    static char left_power,
            right_power;

    /* Drive motors face opposite directions, so reverse one side. */
    LEFT_MOTOR_POWER = -rc_read_data(TANK_DRIVE_LEFT_CHAN);
    RIGHT_MOTOR_POWER = rc_read_data(TANK_DRIVE_RIGHT_CHAN);

    /* Drive motors */
    pwm_write(RIGHT_DRIVE_PORT, right_power);
    pwm_write(LEFT_DRIVE_PORT, left_power);
}

/*************** ARCADE DRIVE ROUTINE ***************/
void    arcade_drive_routine(void)
{
    char left_power, right_power,
            joy_x, joy_y;

    joy_x = rc_read_data(ARCADE_DRIVE_X_CHAN);
    joy_y = -rc_read_data(ARCADE_DRIVE_Y_CHAN);
    arcade_drive(joy_x, joy_y, PWM_MAX, &left_power, &right_power);
    // printf("%d %d %d %d\n", joy_x, joy_y, left_power, right_power);

    /* Drive motors */
    LEFT_MOTOR_POWER = left_power;
    RIGHT_MOTOR_POWER = -right_power;
}

/*************** AUTONOMOUS ROUTINE ***************/
void    autonomous_routine0(void){
    int i;
    DPRINTF("Starting autonomous routine...\n");
    //controller_begin_autonomous_mode(); // uncomment to disable RC interruption

    // start driving forward
    pwm_write(RIGHT_DRIVE_PORT, -AUTON_DRIVE_SPEED);
    pwm_write(LEFT_DRIVE_PORT, AUTON_DRIVE_SPEED);
    controller_submit_data(WAIT);

    // RUN FOR ~20 SECONDS OR UNTIL KILL COMMAND
    // pauses if signal is lost
    for(i=0; (rc_read_data(6) != -127) && (i < 400);i++)
    {
        delay_msec(50);
        if ( io_read_digital(LEFT_BUMPER_PORT) == 0 )
        {

            if ( io_read_digital(RIGHT_BUMPER_PORT) == 0 )
            {
                DPRINTF("Bump left\n");
                bump_front();
            }
            else
                bump_front_left();
        }
        else if ( io_read_digital(RIGHT_BUMPER_PORT) == 0 )
        {
            DPRINTF("Bump right\n");
            bump_front_right();
        }
        controller_submit_data(NO_WAIT);
    }
    pwm_write(RIGHT_DRIVE_PORT, MOTOR_STOP);
    pwm_write(LEFT_DRIVE_PORT, MOTOR_STOP);
    controller_submit_data(WAIT);

    //controller_end_autonomous_mode(); // uncomment to disable RC interruption
    DPRINTF("Ending autonomous routine...\n");
}


/*************** BUMP ROUTINES ***************/

/*************** BUMP FRONT LEFT ***************/
void bump_front_left()
{
    int reset_left,reset_right;
    reset_right = pwm_read(RIGHT_DRIVE_PORT);
    reset_left = pwm_read(LEFT_DRIVE_PORT);

    // reverse
    pwm_write(RIGHT_DRIVE_PORT, AUTON_DRIVE_SPEED);
    pwm_write(LEFT_DRIVE_PORT, -AUTON_DRIVE_SPEED);
    controller_submit_data(WAIT);
    delay_msec(500);

    // turn right
    pwm_write(LEFT_DRIVE_PORT, AUTON_DRIVE_SPEED);
    pwm_write(RIGHT_DRIVE_PORT, AUTON_DRIVE_SPEED);
    controller_submit_data(WAIT);
    delay_msec(500);

    // as you were
    pwm_write(RIGHT_DRIVE_PORT, reset_right);
    pwm_write(LEFT_DRIVE_PORT, reset_left);
    controller_submit_data(WAIT);
    delay_msec(100);

}

/*************** BUMP FRONT RIGHT ***************/
void bump_front_right() {

    int reset_left,reset_right;
    reset_right = pwm_read(RIGHT_DRIVE_PORT);
    reset_left = pwm_read(LEFT_DRIVE_PORT);

    // reverse
    pwm_write(RIGHT_DRIVE_PORT, AUTON_DRIVE_SPEED);
    pwm_write(LEFT_DRIVE_PORT, -AUTON_DRIVE_SPEED);
    controller_submit_data(WAIT);
    delay_msec(500);

    // turn left
    pwm_write(RIGHT_DRIVE_PORT, -AUTON_DRIVE_SPEED);
    pwm_write(LEFT_DRIVE_PORT, -AUTON_DRIVE_SPEED);
    controller_submit_data(WAIT);
    delay_msec(500);

    // as you were
    pwm_write(RIGHT_DRIVE_PORT, reset_right);
    pwm_write(LEFT_DRIVE_PORT, reset_left);
    controller_submit_data(WAIT);
    delay_msec(100);

}

/*************** BUMP FRONT ***************/
void bump_front()
{
    int reset_left,reset_right;
    reset_right = pwm_read(RIGHT_DRIVE_PORT);
    reset_left = pwm_read(LEFT_DRIVE_PORT);

    // reverse
    pwm_write(RIGHT_DRIVE_PORT, -AUTON_DRIVE_SPEED);
    pwm_write(LEFT_DRIVE_PORT, AUTON_DRIVE_SPEED);
    controller_submit_data(WAIT);
    delay_msec(500);

    // do an about-face
    pwm_write(RIGHT_DRIVE_PORT, AUTON_DRIVE_SPEED);
    controller_submit_data(WAIT);
    delay_msec(2700);

    // as you were
    pwm_write(RIGHT_DRIVE_PORT, reset_right);
    pwm_write(LEFT_DRIVE_PORT, reset_left);
    controller_submit_data(WAIT);
    delay_msec(100);
}


// check if data is available
char usart_data_available(void)
{
    return PIR1bits.RCIF;
}

// check if data is available and return if it is
char usart_get_byte_available(void)
{
    if(PIR1bits.RCIF)
        return RCREG;
    else
        return 0;
}

// get last byte available
char usart_get_byte(void)
{
    return RCREG;
}

/*
 * CODE:
 *
 * +++ Put tone control in main loop for timing.
 *
 * +++ Display actual temp as XX.Y instead of XX.YY. Then can look at target temp, actual temp, and valve setpoint.
 *     If none have changed since the last time display was updated, then don't update display.
 *
 * +++ PID control flame
 *
 * +++ Could use a class to make new object for each state and just call init() and update() methods on a pointer to a display object.
 *
 * OTHER:
 * 1. Calibrate temp sensor
 */




/* Ideas
 * - Think I can use singleton programming pattern for utils and disp. 
 */

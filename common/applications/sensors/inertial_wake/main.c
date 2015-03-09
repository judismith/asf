/**
 * \file
 *
 * \brief Common Sensor Service Inertial Sensor Wake Event Example
 *
 * Copyright (c) 2011-2012 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

/**
 * \mainpage
 *
 * \section intro Introduction
 *
 * This application demonstrates the use of sensor events generated by the
 * accelerometer and/or gyroscope devices installed on an Atmel Sensors Xplained
 * board.  The application sets up the sensor event handler(s), then places
 * the microcontroller in a low-power sleep state.  When the specified
 * sensor event occurs, the system wakes up, reads and displays sensor data,
 * and re-enters the sleep mode.  This wake/sleep cycle repeats indefinitely.
 *
 * \section contactinfo Contact Information
 * For further information, visit
 * <a href="http://www.atmel.com/avr">Atmel AVR</a>.\n
 * Support and FAQ: http://support.atmel.no/
 */

#include <stdio.h>
#include <asf.h>
#include <led.h>

/* Configuration Constants */
#define USE_ACCEL          (true) /* If true, init & read accel */
#define ACCEL_WAKE         (true) /* If true, use accel any-motion to wake up */
#define ACCEL_MOT_THRESH   (250)  /* Accel any-motion threshold (milli-g) */

#define USE_GYRO           (false) /* If true, init & read gyro */
#define GYRO_WAKE          (false) /* If true, use gyro new data to wake up */
#define GYRO_SLEEP         (false) /* If true, put gyro in sleep mode */
#define GYRO_SAMPLE_RATE   (100)   /* Gyro sample rate (Hz) */
#define GYRO_RESTART_DELAY (50)    /* Gyro restart (after sleep) delay (msec) */

#define USE_PRINTF         (false)
#define SCALED_DATA        (true)

#if UC3
/* UC3 Sleep Mode to use, one of: */
/*   SLEEPMGR_ACTIVE, SLEEPMGR_IDLE, SLEEPMGR_FROZEN, SLEEPMGR_STDBY, */
/*   SLEEPMGR_STOP, SLEEPMGR_DEEPSTOP, SLEEPMGR_STATIC, */
/*   SLEEPMGR_SHUTDOWN (UC3L only) */
#  define SLEEP_MODE     (SLEEPMGR_FROZEN)   /* sleep mode to use */
#elif XMEGA
/* XMega Sleep Mode to use, one of: */
/*   SLEEPMGR_ACTIVE, SLEEPMGR_IDLE, SLEEPMGR_ESTDBY, SLEEPMGR_PSAVE, */
/*   SLEEPMGR_STDBY, SLEEPMGR_PDOWN */
#  define SLEEP_MODE     (SLEEPMGR_IDLE)     /* sleep mode to use */
#endif

/* LED definitions */
#if (BOARD == UC3_L0_XPLAINED)
#  define ACTIVITY_LED  LED4        /* LED to show awake/operating */
#  define ACCEL_LED     LED1        /* LED to indicate accel interrupt */
#  define GYRO_LED      LED3        /* LED to indicate gyro interrupt */
#elif (BOARD == UC3_A3_XPLAINED)
#  define ACTIVITY_LED  LED0        /* LED to show awake/operating */
#  define ACCEL_LED     LED1        /* LED to indicate accel interrupt */
#  define GYRO_LED      LED3        /* LED to indicate gyro interrupt */
#elif (BOARD == XMEGA_A1_XPLAINED) || (BOARD == XMEGA_B1_XPLAINED) || \
	(BOARD == XMEGA_A3BU_XPLAINED)
#  define ACTIVITY_LED  LED0        /* LED to show awake/operating */
#  define ACCEL_LED     LED2        /* LED to indicate accel interrupt */
#  define GYRO_LED      LED3        /* LED to indicate gyro interrupt */
#endif

/* Set up sensor data storage and data formats. */
sensor_t accelerometer; /* Accelerometer descriptor */
volatile sensor_data_t acceleration = { .scaled = SCALED_DATA };

sensor_t gyroscope;     /* Gyroscope descriptor */
volatile sensor_data_t rotation    = { .scaled = SCALED_DATA };


#if (USE_ACCEL == true)
/** \internal Accelerometer Event Callback Routine */
static void acceleration_event(volatile sensor_event_data_t *event_data,
		volatile void *arg)
{
	/* Save a copy of the event data. */
	acceleration = event_data->data;

	LED_Toggle(ACCEL_LED);
}
#endif

#if (GYRO_WAKE == true)
/** \internal Gyroscope Event Callback Routine */
static void rotation_event(volatile sensor_event_data_t *event_data,
		volatile void *arg)
{
	/* Save a copy of the event data. */
	rotation = event_data->data;

	LED_Toggle(GYRO_LED);
}
#endif

/** \brief Inertial sensor demo application entry
 *
 * After initializing the Xplained platform and sensor boards, this application
 * attaches descriptors to the accelerometer and gyroscope devices on
 * an Xplained inertial sensor board.  The sensor data, which is formatted and
 * printed via printf() after being read, can be viewed with a serial terminal
 * application on a machine attached to the USB interface on the Xplained
 * board.
 */
int main(void)
{
	/* Initialize the Xplained (UC3 or XMEGA) platform & sensor boards. */
	sensor_platform_init();

	LED_On(ACTIVITY_LED);

	/* Initialize the MCU sleep manager API and specify a sleep mode. */
	sleepmgr_init();
	sleepmgr_lock_mode(SLEEP_MODE);

#if (USE_ACCEL == true)
	/* Attach accelerometer */
	sensor_attach(&accelerometer, SENSOR_TYPE_ACCELEROMETER, 0, 0);

	if (accelerometer.err) {
		puts("\r\nAccelerometer initialization error.");

		while (true) {
			/* Error occurred, loop forever */
		}
	}

	/* Enable motion event */
	sensor_set_threshold(&accelerometer, SENSOR_THRESHOLD_MOTION,
			ACCEL_MOT_THRESH);

	sensor_add_event(&accelerometer, SENSOR_EVENT_MOTION,
			acceleration_event, 0, true);

	/* Put the accelerometer into a low-power mode (if available) */
	sensor_set_state(&accelerometer, SENSOR_STATE_LOW_POWER);
#endif

#if (USE_GYRO == true)
	/* Attach gyroscope */
	sensor_attach(&gyroscope, SENSOR_TYPE_GYROSCOPE, 0, 0);

	if (gyroscope.err) {
		puts("\r\nGyroscope initialization error.");

		while (true) {
			/* Error occurred, loop forever */
		}
	}

	sensor_set_sample_rate(&gyroscope, GYRO_SAMPLE_RATE);

#  if (GYRO_WAKE == true)
	/* Enable gyroscope new data event for wakeup */
	sensor_add_event(&gyroscope, SENSOR_EVENT_NEW_DATA,
			rotation_event, 0, true);
#  elif (GYRO_SLEEP == true)
	/* Put gyro in low-power sleep mode until accelerometer wakes system up */
	sensor_set_state(&gyroscope, SENSOR_STATE_SLEEP);
#  endif
#endif

	while (true) {
		LED_Off(ACTIVITY_LED);/* turn off while asleep */

		/* Put device in low power sleep mode until woken up by an interrupt */
		sleepmgr_enter_sleep(); /* enter specified sleep mode */

		/* Device has woken up */
		LED_On(ACTIVITY_LED);             /* turn on while awake */

#if ((USE_GYRO == true) && (GYRO_WAKE == false))
#  if (GYRO_SLEEP == true)
		/* Wake up gyroscope, wait for device to settle */
		sensor_set_state(&gyroscope, SENSOR_STATE_NORMAL);
		delay_ms(GYRO_RESTART_DELAY);

		/* Read gyroscope and put it back to sleep */
		sensor_get_rotation(&gyroscope, &rotation);
		sensor_set_state(&gyroscope, SENSOR_STATE_SLEEP);
#  else
		/* Read gyro in response to accelerometer wake */
		sensor_get_rotation(&gyroscope, &rotation); /* read gyro now */
#  endif
#endif

#if (USE_PRINTF == true)
		const char *const format = SCALED_DATA ?
				"acc = [%5d, %5d, %5d]  rot = [%5d, %5d, %5d]\r\n"
				:
				"acc = [%.5x, %.5x, %.5x]  rot = [%.5x, %.5x, %.5x]\r\n";

		/* Print accelerometer & gyroscope values */
		printf(format,
				/* data from motion event handler */
				(int16_t)acceleration.axis.x,
				(int16_t)acceleration.axis.y,
				(int16_t)acceleration.axis.z,
				
				/* data from sensor_get_rotation() (if GYRO_WAKE==false), or 
				 * from the gyro new data event handler */
				(int16_t)rotation.axis.x,
				(int16_t)rotation.axis.y,
				(int16_t)rotation.axis.z
		);
#endif

		/* Minimum active time is 100 msec */
		delay_ms(100);
	}

	return 0;
}

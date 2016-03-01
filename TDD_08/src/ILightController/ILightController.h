/*
 * ILigthContoller.h
 *
 *  Created on: 13 de feb. de 2016
 *      Author: maxi
 */

#ifndef SRC_ILIGHTCONTROLLER_ILIGHTCONTROLLER_H_
#define SRC_ILIGHTCONTROLLER_ILIGHTCONTROLLER_H_

/*
#if ARDUINO
#include <Arduino.h>
#else
#include <inttypes.h>
typedef uint8_t byte;
#endif
*/

//IMPLEMENTING PURE VIRTUAL FUNCTIONS
class ILightController
{
public:
	ILightController(){};
	virtual ~ILightController(){};
	virtual void On(int id) = 0 ;
	virtual void Off(int id) = 0;
protected:

private:

};
#endif /* SRC_ILIGHTCONTROLLER_ILIGHTCONTROLLER_H_ */

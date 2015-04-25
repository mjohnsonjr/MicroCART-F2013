#ifndef MODULE_H
#define MODULE_H

#include <string>
#include <vector>
#include "MCTStructures.h"

//To add another module type you must increase size and add the type to
//the enumeration list and update the MCTController class for each
// method that has MODULE_TYPE as an argument
#define MODULE_TYPE_SIZE 5
enum MODULE_TYPE {ORIENTATION, DIRECTION, POSITION, COMMUNICATION, CONTROL};

/** @brief Interface for modules.
  * @details This class is used to contain the functions for specific
  *          modules for the MicroCART ground station to determine the
  *          current characteristics of the UAV.
  */
class Module
{
protected:
    //! The name of the module.
    std::string modName;

    //! Keeps track of positioning info.
    MCTposition modPosition;

    //! Keeps track of orientation info.
    MCTorientation modOrientation;

    //! Keeps track of heading info.
    double modDirection;

public:
    /** @brief Constructs a module with no name.
      */
    Module();

    /** @brief Constructs a module with an specified name.
      * @param[in] name The name of the module.
      */
    Module(std::string);

    /** @brief Default destructor for Module
      */
    virtual ~Module() {}

    /** @brief Gets the name of the module.
      * @return String representation of the module's name.
      */
    std::string getName()   {return modName;}

    /** @brief Initializes the module and starts its funcitons.
      * @details This needs to be reimplemented on a per module basis.
      * @return True if successful.
      */
    virtual bool start()    {return false;}

    /** @brief Updates the internal state of the module.
      * @details This needs to be reimplemented on a per module basis.
      * @return True if successful.
      */
    virtual bool update()   {return false;}

    /** @brief Stops all functions of the module.
      * @details This needs to be reimplemented on a per module basis.
      * @return True if successful.
      */
    virtual bool stop()     {return false;}


    /** @brief Checks if this module is responsible for communicating with the quadcopter.
      * @details This needs to be reimplemented on a per module basis.
      * @return True if this module is responsible for communicating with the quadcopter.
      */
    virtual bool isCommMod() {return false;}

    /** @brief Checks if this module is responsible for tracking the heading of the quadcopter.
      * @details This needs to be reimplemented on a per module basis.
      * @return True if this module is responsible for tracking the heading of the quadcopter.
      */
    virtual bool isDirMod()  {return false;}

    /** @brief Checks if this module is responsible for tracking the heading of the quadcopter.
      * @details This needs to be reimplemented on a per module basis.
      * @return True if this module is responsible for tracking the heading of the quadcopter.
      */
    virtual bool isPosMod()  {return false;}

    /** @brief Checks if this module is responsible for tracking the orientation of the quadcopter.
      * @details This needs to be reimplemented on a per module basis.
      * @return True if this module is responsible for tracking the orientation of the quadcopter.
      */
    virtual bool isOriMod()  {return false;}

    /** @brief Checks if this module is responsible for manually controlling the quadcopter.
      * @details This needs to be reimplemented on a per module basis.
      * @return True if this module is responsible for manually controlling the quadcopter.
      */
    virtual bool isContMod() {return false;}


    /** @brief Sets specific values to a module.
      * @details What the values are depends on the type of module.
      * @param[in] *data Pointer to a data array.
      * @param[in] size Number of elements in the data array.
      * @return True if successful.
      */
    virtual bool setModValues(double *data, int size) {return false;}

    /** @brief Gets specific values from a module.
      * @details What the values are depends on the type of module.
      * @param[out] *data Pointer to a data array.
      * @param[in] size Number of elements in the data array.
      * @return True if successful.
      */
    virtual bool getModValues(double *data, int size) {return false;}
    virtual bool getAllModValues(double *data, int size) {return false;}
    /**
      * Get functions for position orientation and direction
     **/

    /** @brief Gets the position of the quadcopter.
      * @return MCTposition struture containing position information.
      */
    MCTposition getPosition()           {return modPosition;}

    /** @brief Gets the heading of the quadcopter.
      * @return MCTposition struture containing position information.
      */
    double getDirection()               {return modDirection;}

    /** @brief Gets the orientation of the quadcopter.
      * @return MCTorientation struture containing orientation information.
      */
    MCTorientation getOrientation()     {return modOrientation;}
};

#endif // MODULE_H


// Auto-generated. Do not edit!

// (in-package ros_can_interface.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class navigator_navigationMessage {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.nav_currentX = null;
      this.nav_currentY = null;
      this.nav_currentAngle = null;
      this.nav_currentState = null;
    }
    else {
      if (initObj.hasOwnProperty('nav_currentX')) {
        this.nav_currentX = initObj.nav_currentX
      }
      else {
        this.nav_currentX = 0.0;
      }
      if (initObj.hasOwnProperty('nav_currentY')) {
        this.nav_currentY = initObj.nav_currentY
      }
      else {
        this.nav_currentY = 0.0;
      }
      if (initObj.hasOwnProperty('nav_currentAngle')) {
        this.nav_currentAngle = initObj.nav_currentAngle
      }
      else {
        this.nav_currentAngle = 0.0;
      }
      if (initObj.hasOwnProperty('nav_currentState')) {
        this.nav_currentState = initObj.nav_currentState
      }
      else {
        this.nav_currentState = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type navigator_navigationMessage
    // Serialize message field [nav_currentX]
    bufferOffset = _serializer.float32(obj.nav_currentX, buffer, bufferOffset);
    // Serialize message field [nav_currentY]
    bufferOffset = _serializer.float32(obj.nav_currentY, buffer, bufferOffset);
    // Serialize message field [nav_currentAngle]
    bufferOffset = _serializer.float32(obj.nav_currentAngle, buffer, bufferOffset);
    // Serialize message field [nav_currentState]
    bufferOffset = _serializer.int8(obj.nav_currentState, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type navigator_navigationMessage
    let len;
    let data = new navigator_navigationMessage(null);
    // Deserialize message field [nav_currentX]
    data.nav_currentX = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [nav_currentY]
    data.nav_currentY = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [nav_currentAngle]
    data.nav_currentAngle = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [nav_currentState]
    data.nav_currentState = _deserializer.int8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 13;
  }

  static datatype() {
    // Returns string type for a message object
    return 'ros_can_interface/navigator_navigationMessage';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '90176a0f60fd26d08c0aaca4ecb268df';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 nav_currentX
    float32 nav_currentY
    float32 nav_currentAngle
    int8 nav_currentState
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new navigator_navigationMessage(null);
    if (msg.nav_currentX !== undefined) {
      resolved.nav_currentX = msg.nav_currentX;
    }
    else {
      resolved.nav_currentX = 0.0
    }

    if (msg.nav_currentY !== undefined) {
      resolved.nav_currentY = msg.nav_currentY;
    }
    else {
      resolved.nav_currentY = 0.0
    }

    if (msg.nav_currentAngle !== undefined) {
      resolved.nav_currentAngle = msg.nav_currentAngle;
    }
    else {
      resolved.nav_currentAngle = 0.0
    }

    if (msg.nav_currentState !== undefined) {
      resolved.nav_currentState = msg.nav_currentState;
    }
    else {
      resolved.nav_currentState = 0
    }

    return resolved;
    }
};

module.exports = navigator_navigationMessage;

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

class master_navigationMessage {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.nav_targetX = null;
      this.nav_targetY = null;
      this.nav_targetAngle = null;
      this.nav_isForward = null;
    }
    else {
      if (initObj.hasOwnProperty('nav_targetX')) {
        this.nav_targetX = initObj.nav_targetX
      }
      else {
        this.nav_targetX = 0.0;
      }
      if (initObj.hasOwnProperty('nav_targetY')) {
        this.nav_targetY = initObj.nav_targetY
      }
      else {
        this.nav_targetY = 0.0;
      }
      if (initObj.hasOwnProperty('nav_targetAngle')) {
        this.nav_targetAngle = initObj.nav_targetAngle
      }
      else {
        this.nav_targetAngle = 0.0;
      }
      if (initObj.hasOwnProperty('nav_isForward')) {
        this.nav_isForward = initObj.nav_isForward
      }
      else {
        this.nav_isForward = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type master_navigationMessage
    // Serialize message field [nav_targetX]
    bufferOffset = _serializer.float32(obj.nav_targetX, buffer, bufferOffset);
    // Serialize message field [nav_targetY]
    bufferOffset = _serializer.float32(obj.nav_targetY, buffer, bufferOffset);
    // Serialize message field [nav_targetAngle]
    bufferOffset = _serializer.float32(obj.nav_targetAngle, buffer, bufferOffset);
    // Serialize message field [nav_isForward]
    bufferOffset = _serializer.bool(obj.nav_isForward, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type master_navigationMessage
    let len;
    let data = new master_navigationMessage(null);
    // Deserialize message field [nav_targetX]
    data.nav_targetX = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [nav_targetY]
    data.nav_targetY = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [nav_targetAngle]
    data.nav_targetAngle = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [nav_isForward]
    data.nav_isForward = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 13;
  }

  static datatype() {
    // Returns string type for a message object
    return 'ros_can_interface/master_navigationMessage';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'fe1a2421738fe61ce953bf0c9b6e4f00';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 nav_targetX
    float32 nav_targetY
    float32 nav_targetAngle
    bool nav_isForward
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new master_navigationMessage(null);
    if (msg.nav_targetX !== undefined) {
      resolved.nav_targetX = msg.nav_targetX;
    }
    else {
      resolved.nav_targetX = 0.0
    }

    if (msg.nav_targetY !== undefined) {
      resolved.nav_targetY = msg.nav_targetY;
    }
    else {
      resolved.nav_targetY = 0.0
    }

    if (msg.nav_targetAngle !== undefined) {
      resolved.nav_targetAngle = msg.nav_targetAngle;
    }
    else {
      resolved.nav_targetAngle = 0.0
    }

    if (msg.nav_isForward !== undefined) {
      resolved.nav_isForward = msg.nav_isForward;
    }
    else {
      resolved.nav_isForward = false
    }

    return resolved;
    }
};

module.exports = master_navigationMessage;

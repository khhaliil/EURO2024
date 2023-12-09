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

class lidar_stopSignal {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.stopSignalState = null;
    }
    else {
      if (initObj.hasOwnProperty('stopSignalState')) {
        this.stopSignalState = initObj.stopSignalState
      }
      else {
        this.stopSignalState = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type lidar_stopSignal
    // Serialize message field [stopSignalState]
    bufferOffset = _serializer.bool(obj.stopSignalState, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type lidar_stopSignal
    let len;
    let data = new lidar_stopSignal(null);
    // Deserialize message field [stopSignalState]
    data.stopSignalState = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a message object
    return 'ros_can_interface/lidar_stopSignal';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '096988a79a296361c0020ef3b05a1428';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool stopSignalState
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new lidar_stopSignal(null);
    if (msg.stopSignalState !== undefined) {
      resolved.stopSignalState = msg.stopSignalState;
    }
    else {
      resolved.stopSignalState = false
    }

    return resolved;
    }
};

module.exports = lidar_stopSignal;

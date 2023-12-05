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

class master_acknowledgSignal {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.master_acknowledgeSignal = null;
    }
    else {
      if (initObj.hasOwnProperty('master_acknowledgeSignal')) {
        this.master_acknowledgeSignal = initObj.master_acknowledgeSignal
      }
      else {
        this.master_acknowledgeSignal = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type master_acknowledgSignal
    // Serialize message field [master_acknowledgeSignal]
    bufferOffset = _serializer.bool(obj.master_acknowledgeSignal, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type master_acknowledgSignal
    let len;
    let data = new master_acknowledgSignal(null);
    // Deserialize message field [master_acknowledgeSignal]
    data.master_acknowledgeSignal = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a message object
    return 'ros_can_interface/master_acknowledgSignal';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'db74e876059988b41de2c46733c73690';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool master_acknowledgeSignal
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new master_acknowledgSignal(null);
    if (msg.master_acknowledgeSignal !== undefined) {
      resolved.master_acknowledgeSignal = msg.master_acknowledgeSignal;
    }
    else {
      resolved.master_acknowledgeSignal = false
    }

    return resolved;
    }
};

module.exports = master_acknowledgSignal;

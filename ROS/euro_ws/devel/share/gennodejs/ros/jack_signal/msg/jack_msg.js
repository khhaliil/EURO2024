// Auto-generated. Do not edit!

// (in-package jack_signal.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class jack_msg {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.jack_state = null;
    }
    else {
      if (initObj.hasOwnProperty('jack_state')) {
        this.jack_state = initObj.jack_state
      }
      else {
        this.jack_state = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type jack_msg
    // Serialize message field [jack_state]
    bufferOffset = _serializer.bool(obj.jack_state, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type jack_msg
    let len;
    let data = new jack_msg(null);
    // Deserialize message field [jack_state]
    data.jack_state = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a message object
    return 'jack_signal/jack_msg';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '452828b561eb89702df2b017469a83ed';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool jack_state
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new jack_msg(null);
    if (msg.jack_state !== undefined) {
      resolved.jack_state = msg.jack_state;
    }
    else {
      resolved.jack_state = false
    }

    return resolved;
    }
};

module.exports = jack_msg;

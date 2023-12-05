// Auto-generated. Do not edit!

// (in-package path_planner.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------


//-----------------------------------------------------------

class PathPlanRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.current_pose = null;
      this.target_point = null;
      this.obstacle = null;
    }
    else {
      if (initObj.hasOwnProperty('current_pose')) {
        this.current_pose = initObj.current_pose
      }
      else {
        this.current_pose = new geometry_msgs.msg.Pose2D();
      }
      if (initObj.hasOwnProperty('target_point')) {
        this.target_point = initObj.target_point
      }
      else {
        this.target_point = new geometry_msgs.msg.Pose2D();
      }
      if (initObj.hasOwnProperty('obstacle')) {
        this.obstacle = initObj.obstacle
      }
      else {
        this.obstacle = new geometry_msgs.msg.Pose2D();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type PathPlanRequest
    // Serialize message field [current_pose]
    bufferOffset = geometry_msgs.msg.Pose2D.serialize(obj.current_pose, buffer, bufferOffset);
    // Serialize message field [target_point]
    bufferOffset = geometry_msgs.msg.Pose2D.serialize(obj.target_point, buffer, bufferOffset);
    // Serialize message field [obstacle]
    bufferOffset = geometry_msgs.msg.Pose2D.serialize(obj.obstacle, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PathPlanRequest
    let len;
    let data = new PathPlanRequest(null);
    // Deserialize message field [current_pose]
    data.current_pose = geometry_msgs.msg.Pose2D.deserialize(buffer, bufferOffset);
    // Deserialize message field [target_point]
    data.target_point = geometry_msgs.msg.Pose2D.deserialize(buffer, bufferOffset);
    // Deserialize message field [obstacle]
    data.obstacle = geometry_msgs.msg.Pose2D.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 72;
  }

  static datatype() {
    // Returns string type for a service object
    return 'path_planner/PathPlanRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ef3014d0c5a51d27ddb6567b5cbf3205';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # Current robot position and angle
    geometry_msgs/Pose2D current_pose
    
    # Target point
    geometry_msgs/Pose2D target_point
    
    # Presented obstacle position
    geometry_msgs/Pose2D obstacle
    
    
    ================================================================================
    MSG: geometry_msgs/Pose2D
    # Deprecated
    # Please use the full 3D pose.
    
    # In general our recommendation is to use a full 3D representation of everything and for 2D specific applications make the appropriate projections into the plane for their calculations but optimally will preserve the 3D information during processing.
    
    # If we have parallel copies of 2D datatypes every UI and other pipeline will end up needing to have dual interfaces to plot everything. And you will end up with not being able to use 3D tools for 2D use cases even if they're completely valid, as you'd have to reimplement it with different inputs and outputs. It's not particularly hard to plot the 2D pose or compute the yaw error for the Pose message and there are already tools and libraries that can do this for you.
    
    
    # This expresses a position and orientation on a 2D manifold.
    
    float64 x
    float64 y
    float64 theta
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new PathPlanRequest(null);
    if (msg.current_pose !== undefined) {
      resolved.current_pose = geometry_msgs.msg.Pose2D.Resolve(msg.current_pose)
    }
    else {
      resolved.current_pose = new geometry_msgs.msg.Pose2D()
    }

    if (msg.target_point !== undefined) {
      resolved.target_point = geometry_msgs.msg.Pose2D.Resolve(msg.target_point)
    }
    else {
      resolved.target_point = new geometry_msgs.msg.Pose2D()
    }

    if (msg.obstacle !== undefined) {
      resolved.obstacle = geometry_msgs.msg.Pose2D.Resolve(msg.obstacle)
    }
    else {
      resolved.obstacle = new geometry_msgs.msg.Pose2D()
    }

    return resolved;
    }
};

class PathPlanResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.new_path = null;
    }
    else {
      if (initObj.hasOwnProperty('new_path')) {
        this.new_path = initObj.new_path
      }
      else {
        this.new_path = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type PathPlanResponse
    // Serialize message field [new_path]
    // Serialize the length for message field [new_path]
    bufferOffset = _serializer.uint32(obj.new_path.length, buffer, bufferOffset);
    obj.new_path.forEach((val) => {
      bufferOffset = geometry_msgs.msg.Pose2D.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PathPlanResponse
    let len;
    let data = new PathPlanResponse(null);
    // Deserialize message field [new_path]
    // Deserialize array length for message field [new_path]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.new_path = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.new_path[i] = geometry_msgs.msg.Pose2D.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 24 * object.new_path.length;
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'path_planner/PathPlanResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '60d0cf4e7774342781ba2023adea4661';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    # Array of intermediate points for the new path
    geometry_msgs/Pose2D[] new_path
    
    ================================================================================
    MSG: geometry_msgs/Pose2D
    # Deprecated
    # Please use the full 3D pose.
    
    # In general our recommendation is to use a full 3D representation of everything and for 2D specific applications make the appropriate projections into the plane for their calculations but optimally will preserve the 3D information during processing.
    
    # If we have parallel copies of 2D datatypes every UI and other pipeline will end up needing to have dual interfaces to plot everything. And you will end up with not being able to use 3D tools for 2D use cases even if they're completely valid, as you'd have to reimplement it with different inputs and outputs. It's not particularly hard to plot the 2D pose or compute the yaw error for the Pose message and there are already tools and libraries that can do this for you.
    
    
    # This expresses a position and orientation on a 2D manifold.
    
    float64 x
    float64 y
    float64 theta
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new PathPlanResponse(null);
    if (msg.new_path !== undefined) {
      resolved.new_path = new Array(msg.new_path.length);
      for (let i = 0; i < resolved.new_path.length; ++i) {
        resolved.new_path[i] = geometry_msgs.msg.Pose2D.Resolve(msg.new_path[i]);
      }
    }
    else {
      resolved.new_path = []
    }

    return resolved;
    }
};

module.exports = {
  Request: PathPlanRequest,
  Response: PathPlanResponse,
  md5sum() { return 'a9186ff1c0833e5c6cc2915c1b9610f7'; },
  datatype() { return 'path_planner/PathPlan'; }
};

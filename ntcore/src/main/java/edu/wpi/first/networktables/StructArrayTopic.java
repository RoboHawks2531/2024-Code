// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

package edu.wpi.first.networktables;

import edu.wpi.first.util.struct.Struct;
import edu.wpi.first.util.struct.StructBuffer;

/**
 * NetworkTables struct-encoded array value topic.
 *
 * @param <T> value class
 */
public final class StructArrayTopic<T> extends Topic {
  private StructArrayTopic(Topic topic, Struct<T> struct) {
    super(topic.m_inst, topic.m_handle);
    m_struct = struct;
  }

  private StructArrayTopic(NetworkTableInstance inst, int handle, Struct<T> struct) {
    super(inst, handle);
    m_struct = struct;
  }

  /**
   * Create a StructArrayTopic from a generic topic.
   *
   * @param <T> value class (inferred from struct)
   * @param topic generic topic
   * @param struct struct serialization implementation
   * @return StructArrayTopic for value class
   */
  public static <T> StructArrayTopic<T> wrap(Topic topic, Struct<T> struct) {
    return new StructArrayTopic<T>(topic, struct);
  }

  /**
   * Create a StructArrayTopic from a native handle; generally
   * NetworkTableInstance.getStructArrayTopic() should be used instead.
   *
   * @param <T> value class (inferred from struct)
   * @param inst Instance
   * @param handle Native handle
   * @param struct struct serialization implementation
   * @return StructArrayTopic for value class
   */
  public static <T> StructArrayTopic<T> wrap(
      NetworkTableInstance inst, int handle, Struct<T> struct) {
    return new StructArrayTopic<T>(inst, handle, struct);
  }

  /**
   * Create a new subscriber to the topic.
   *
   * <p>The subscriber is only active as long as the returned object is not closed.
   *
   * <p>Subscribers that do not match the published data type do not return any values. To determine
   * if the data type matches, use the appropriate Topic functions.
   *
   * @param defaultValue default value used when a default is not provided to a getter function
   * @param options subscribe options
   * @return subscriber
   */
  public StructArraySubscriber<T> subscribe(T[] defaultValue, PubSubOption... options) {
    return new StructArrayEntryImpl<T>(
        this,
        StructBuffer.create(m_struct),
        NetworkTablesJNI.subscribe(
            m_handle, NetworkTableType.kRaw.getValue(), m_struct.getTypeString() + "[]", options),
        defaultValue,
        false);
  }

  /**
   * Create a new publisher to the topic.
   *
   * <p>The publisher is only active as long as the returned object is not closed.
   *
   * <p>It is not possible to publish two different data types to the same topic. Conflicts between
   * publishers are typically resolved by the server on a first-come, first-served basis. Any
   * published values that do not match the topic's data type are dropped (ignored). To determine if
   * the data type matches, use the appropriate Topic functions.
   *
   * @param options publish options
   * @return publisher
   */
  public StructArrayPublisher<T> publish(PubSubOption... options) {
    m_inst.addSchema(m_struct);
    return new StructArrayEntryImpl<T>(
        this,
        StructBuffer.create(m_struct),
        NetworkTablesJNI.publish(
            m_handle, NetworkTableType.kRaw.getValue(), m_struct.getTypeString() + "[]", options),
        null,
        true);
  }

  /**
   * Create a new publisher to the topic, with type string and initial properties.
   *
   * <p>The publisher is only active as long as the returned object is not closed.
   *
   * <p>It is not possible to publish two different data types to the same topic. Conflicts between
   * publishers are typically resolved by the server on a first-come, first-served basis. Any
   * published values that do not match the topic's data type are dropped (ignored). To determine if
   * the data type matches, use the appropriate Topic functions.
   *
   * @param properties JSON properties
   * @param options publish options
   * @return publisher
   * @throws IllegalArgumentException if properties is not a JSON object
   */
  public StructArrayPublisher<T> publishEx(String properties, PubSubOption... options) {
    m_inst.addSchema(m_struct);
    return new StructArrayEntryImpl<T>(
        this,
        StructBuffer.create(m_struct),
        NetworkTablesJNI.publishEx(
            m_handle,
            NetworkTableType.kRaw.getValue(),
            m_struct.getTypeString() + "[]",
            properties,
            options),
        null,
        true);
  }

  /**
   * Create a new entry for the topic.
   *
   * <p>Entries act as a combination of a subscriber and a weak publisher. The subscriber is active
   * as long as the entry is not closed. The publisher is created when the entry is first written
   * to, and remains active until either unpublish() is called or the entry is closed.
   *
   * <p>It is not possible to use two different data types with the same topic. Conflicts between
   * publishers are typically resolved by the server on a first-come, first-served basis. Any
   * published values that do not match the topic's data type are dropped (ignored), and the entry
   * will show no new values if the data type does not match. To determine if the data type matches,
   * use the appropriate Topic functions.
   *
   * @param defaultValue default value used when a default is not provided to a getter function
   * @param options publish and/or subscribe options
   * @return entry
   */
  public StructArrayEntry<T> getEntry(T[] defaultValue, PubSubOption... options) {
    return new StructArrayEntryImpl<T>(
        this,
        StructBuffer.create(m_struct),
        NetworkTablesJNI.getEntry(
            m_handle, NetworkTableType.kRaw.getValue(), m_struct.getTypeString() + "[]", options),
        defaultValue,
        false);
  }

  public Struct<T> getStruct() {
    return m_struct;
  }

  @Override
  public boolean equals(Object other) {
    if (other == this) {
      return true;
    }
    if (!(other instanceof StructArrayTopic)) {
      return false;
    }

    return super.equals(other) && m_struct == ((StructArrayTopic<?>) other).m_struct;
  }

  @Override
  public int hashCode() {
    return super.hashCode() ^ m_struct.hashCode();
  }

  private final Struct<T> m_struct;
}

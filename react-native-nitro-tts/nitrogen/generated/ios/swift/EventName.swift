///
/// EventName.swift
/// This file was generated by nitrogen. DO NOT MODIFY THIS FILE.
/// https://github.com/mrousavy/nitro
/// Copyright © 2024 Marc Rousavy @ Margelo
///

/**
 * Represents the JS union `EventName`, backed by a C++ enum.
 */
public typealias EventName = margelo.nitro.nitrotexttospeech.EventName

public extension EventName {
  /**
   * Get a EventName for the given String value, or
   * return `nil` if the given value was invalid/unknown.
   */
  init?(fromString string: String) {
    switch string {
      case "word":
        self = .word
      case "finish":
        self = .finish
      case "start":
        self = .start
      default:
        return nil
    }
  }

  /**
   * Get the String value this EventName represents.
   */
  var stringValue: String {
    switch self {
      case .word:
        return "word"
      case .finish:
        return "finish"
      case .start:
        return "start"
    }
  }
}

#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>
#include <functional>

class InputControl {

private:
	std::unordered_map<sf::Keyboard::Key, std::unordered_map<sf::Event::EventType, std::function<void()>>> key_event_mapping;

public:
	InputControl() = default;
	void SetMapping(sf::Keyboard::Key key, std::function<void()> fn, sf::Event::EventType eventType) {
        key_event_mapping[key][eventType] = fn;
    }
	void ExecuteKey(sf::Keyboard::Key key, sf::Event::EventType eventType) {
        auto keyIt = key_event_mapping.find(key);
        if (keyIt != key_event_mapping.end()) {
            auto eventIt = keyIt->second.find(eventType);
            if (eventIt != keyIt->second.end()) {
                eventIt->second();
            }
        }
    }

};
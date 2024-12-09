#pragma once
#include <unordered_map>
#include "EventType.h"
#include <functional>

class EventSystem {
private:
	EventSystem() = default;
	~EventSystem() = default;
	struct Listener {
		EventType type;
		std::function<void(const void*)> callback;

		Listener(EventType type, std::function<void(const void*)> callback) : type(type), callback(std::move(callback)) {}

	};
	std::unordered_map<void*, std::vector<Listener>> listeners;

public:
	static EventSystem* getInstance() {
		static EventSystem instance;
		return &instance;
	}

	template<typename EventData>
	void subscribe(EventType type, void* owner, std::function<void(const EventData&)> callback) {
		auto& eventListeners = listeners[owner];
		eventListeners.emplace_back(type, [callback](const void* data) {
			callback(*static_cast<const EventData*>(data));
		});
	}

	template <typename EventData>
	void publish(EventType type, const EventData& data) {
		for (auto& [owner, ownerListeners] : listeners) {
			for (auto& listener : ownerListeners) {
				if (listener.type == type) {
					listener.callback(static_cast<const void*>(&data)); 
				}
			}
		}
	}

	void unsubscribeOwner(void* owner) {
		listeners.erase(owner);
	}

};

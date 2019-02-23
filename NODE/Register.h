#pragma once
#include <map>
#include <string>
#include <functional>
#include <memory>
#include <qdebug.h>
#include <NODE_item.h>
#include <UT_utils.h>
#include <json.hpp>
#include <node_global.h>
using json = nlohmann::json;

struct NODE_EXPORT factory
{
	template<typename T>
	struct register_t
	{
		register_t(const std::string& key)
		{
			factory::get().map_.emplace(key, &register_t<T>::create);
			qDebug() << QString::fromStdString(key);
			//qDebug() << QString::fromStdString(menu);
		}

		template<typename... Args>
		register_t(const std::string& key, Args... args)
		{
			factory::get().map_.emplace(key, &register_t<T>::create);
			auto&& tt = std::forward_as_tuple(args...);
			string menuName = std::get<0>(tt);
			string keyW = std::get<1>(tt);
			//qDebug() << QString::fromStdString(key);
			//qDebug() << QString::fromStdString(menuName);
			//qDebug() << QString::fromStdString(keyW);

			json menu;
			menu["name"] = key;
			menu["menuName"] = menuName;
			menu["key"] = keyW;
			Menus.push_back(menu);
		}


		/*template<typename... Args>
		register_t(const std::string& key, Args... args)
		{
			factory::get().map_.emplace(key, [=] { return new T(args...); });
		}*/
		inline static NODE_item* create() { return new T; }
	};

	inline NODE_item* produce(const std::string& key)
	{
		if (map_.find(key) == map_.end())
			throw std::invalid_argument("the message key is not exist!");

		return map_[key]();
	}

	std::unique_ptr<NODE_item> produce_unique(const std::string& key)
	{
		return std::unique_ptr<NODE_item>(produce(key));
	}

	std::shared_ptr<NODE_item> produce_shared(const std::string& key)
	{
		return std::shared_ptr<NODE_item>(produce(key));
	}
	typedef NODE_item*(*FunPtr)();

	inline static factory& get()
	{
		static factory instance;
		return instance;
	}

private:
	factory() {};
	factory(const factory&) = delete;
	factory(factory&&) = delete;

	std::map<std::string, FunPtr> map_;
};

//std::map<std::string, factory::FunPtr> factory::map_;

#define REGISTER_NODE_VNAME(T) reg_msg_##T##_
#define REGISTER_NODE(T, key, ...) static factory::register_t<T> REGISTER_NODE_VNAME(T)(key, ##__VA_ARGS__);

#pragma once
#include <map>
#include <string>
#include <memory>
#include <functional>
#include "GameObject.h""

class ObjectFactory
{
public:
	GameObject* CreateObject(std::string type, Properties* props);
	void RegisterType(std::string className, std::function<GameObject*(Properties* props)> type);
	static ObjectFactory& get() {
		if (s_instance == nullptr) {
			s_instance = new ObjectFactory();
		}
		return *s_instance;
	}
private:
	ObjectFactory() {}
	static ObjectFactory* s_instance;
	std::map<std::string, std::function<GameObject* (Properties* props)>> m_TypeRegistry;
};

template<class Type>
class Registrar
{
public:
	Registrar(std::string className)
	{
		ObjectFactory::get().RegisterType(className, [](Properties* props)->GameObject* {return new Type(props); });
	}
};
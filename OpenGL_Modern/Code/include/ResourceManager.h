#pragma once

#include <string>
#include <map>
#include <memory>
#include "Textures.h"
#include "Mesh.h"
#include "Debug.h"

namespace Bwt
{
	namespace Resources
	{
		class ResourceManager
		{
			std::map<std::string, std::unique_ptr<IResource>> resources;

		public:
			ResourceManager() {};
			~ResourceManager() {};
			// -------------------------------------------------------------------------------- //    
			// Basic Constructor 
			// -------------------------------------------------------------------------------- //

			/// <summary>
			/// Create a resource from the template and add in the list by the name.
			/// </summary>
			/// <param name="name"> : Name of the resource in string.</param>
			/// <returns> Return an reference of the instance after creation.</returns>
			template <typename T>
			T* Create(const std::string& name)
			{
				Bwt::Core::Debug::AssertFunction(std::is_base_of<IResource, T>::value); // T must inherit from IResource

				auto it = resources.find(name);
				if (it != resources.end())
				{
					resources.erase(it);
				}

				T* newResource = new T();
				resources[name] = std::unique_ptr<IResource>(newResource);

				return newResource;
			}			
			
			/// <summary>
			/// Create a Texture from the template and add in the list by the name.
			/// </summary>
			/// <param name="name"> : Name of the resource in string.</param>
			/// <param name="path"> : The path of the resource in filesystem::path.</param>
			/// <param name="params"> : Optional parameter if you want personalised it resource.</param>
			/// <returns>Return an reference of the instance after creation.</returns>
			template <typename T>
			T* CreateTexture(const std::string& name, const std::filesystem::path& path, const TextureParams& params = TextureParams())
			{
				Bwt::Core::Debug::AssertFunction(std::is_base_of<IResource, T>::value); // T must inherit from IResource

				auto it = resources.find(name);
				if (it != resources.end())
				{
					resources.erase(it);
				}

				T* newResource = new T(path, params);
				resources[name] = std::unique_ptr<IResource>(newResource);

				return newResource;
			}


			/// <summary>
			/// Get a resource from the the list by the name.
			/// </summary>
			/// <param name="name"> : Name of the resource in string.</param>
			/// <returns> Return an reference of the instance if it exist , otherwise it return nullptr </returns>
			template <typename T>
			T* Get(const std::string& name)
			{
				auto it = resources.find(name);
				if (it != resources.end())
				{
					return dynamic_cast<T*>(it->second.get());
				}
				return nullptr;
			}

			/// <summary>
			/// Delete an resources if it exist by the name
			/// </summary>
			/// <param name="name"> : Name of the resource in string.</param>
			/// <returns> Return true if find and deleted, return false if resources doesn't exist. </returns>
			inline bool Delete(const std::string& name)
			{
				return resources.erase(name) > 0;
			}
		};
	}
}
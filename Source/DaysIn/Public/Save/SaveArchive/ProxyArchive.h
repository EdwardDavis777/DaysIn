#pragma once

/*

      Defines proxy archive methods for serialzation of objects.
      Each method expects a struct with at least a uint8 array for 
      binary data.

*/



//Component imports.
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"


//Engine imports.
#include "CoreMinimal.h"


namespace Arch
{

    /*
         Begins parsing all data from the given UObject, and serializes
         all UObject fields marked with a USaveGame into the given package.

         @param Object: pointer to some object you wish to serialize
         data from.

         @param TPackage: reference to a package you wish to serialize
         into, Note; the package must have a ByteData member.

         @tparam TPackage: class type that defines a package to 
         serialize data into.
    */
    template<typename TPackage>
    void SerializeObject(UObject* Object, TPackage& Package)
    {
        if (!Object) return;

        FMemoryWriter Writer(Package.ByteData);
        FObjectAndNameAsStringProxyArchive Ar(Writer, true);
        Ar.ArIsSaveGame = true;
        Object->Serialize(Ar);
    }


    /*
         Deserializes an object from the given package.

         @param Object: pointer to the object you wish to 
         deserialize data into.

         @param Package: reference to a package of data you wish 
         to dump data from.

         @tparam TPackage: class type that defines the package
         to dump data from.
    */
    template<typename TPackage>
    void DeSerializeObject(UObject* Object, TPackage& Package)
    {
        if (!Object) return;

        FMemoryReader Reader(Package.ByteData);
        FObjectAndNameAsStringProxyArchive Ar(Reader, true);
        Ar.ArIsSaveGame = true;
        Object->Serialize(Ar);
    }
}
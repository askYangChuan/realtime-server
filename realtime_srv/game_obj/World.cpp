#include "realtime_srv/common/RealtimeSrvShared.h"


using namespace realtime_srv;



int World::kNewObjId = 1;

void World::Registry( GameObjPtr& obj, ReplicationAction repAction )
{
	if ( repAction == RA_Create )
		RegistGameObj( obj );
	else if ( repAction == RA_Destroy )
		UnregistGameObj( obj );
}

int World::GetNewObjId()
{
	int toRet = kNewObjId++;
	if ( kNewObjId < toRet )
		LOG( "GameObj ID Wrap Around!!! You've been playing way too long..." );
	return toRet;
}

bool World::IsGameObjectExist( int objId )
{
	auto gameObjectIt = ObjIdToGameObjMap_.find( objId );
	return gameObjectIt != ObjIdToGameObjMap_.end();
}

GameObjPtr World::GetGameObject( int objId )
{
	auto gameObjectIt = ObjIdToGameObjMap_.find( objId );
	if ( gameObjectIt != ObjIdToGameObjMap_.end() )
		return gameObjectIt->second;
	else
		return GameObjPtr();
}

void World::RegistGameObj( GameObjPtr& obj )
{
	int newObjId = GetNewObjId();
	obj->SetObjId( newObjId );
	ObjIdToGameObjMap_[newObjId] = obj;

	notifyAllClientCB_( obj, RA_Create );
	auto newClientProxy = obj->GetClientProxy();
	if ( newClientProxy )
	{
		newClientProxy->SetWorld( this );
		for ( const auto& ipair : ObjIdToGameObjMap_ )
		{
			newClientProxy->GetReplicationManager().ReplicateCreate(
				ipair.first, ipair.second->GetAllStateMask() );
		}
	}
}

void World::UnregistGameObj( GameObjPtr& obj )
{
	notifyAllClientCB_( obj, RA_Destroy );
	ObjIdToGameObjMap_.erase( obj->GetObjId() );
}

void World::Update()
{
	vector< GameObjPtr > GameObjsToRem;
	for ( const auto& pair : ObjIdToGameObjMap_ )
	{
		auto go = pair.second;
		if ( go->IsPendingToDestroy() )
			GameObjsToRem.push_back( go );
		else
			go->Update();
	}

	for ( auto& g : GameObjsToRem ) UnregistGameObj( g );
}
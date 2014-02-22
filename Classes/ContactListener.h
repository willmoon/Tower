#include "Box2D/Box2D.h"
#include "cocos2d.h"
#include <list>
using namespace std;
class MyContact
{
public :
	b2Fixture *fixtureA,*fixtureB;
	bool operator==(const MyContact& other) const
	{
		return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
	}

};
class MyContactListener:public b2ContactListener
{
	virtual void BeginContact(b2Contact* contact) 
	{ 
		if(contact)
		{
			MyContact mc;
			mc.fixtureA=contact->GetFixtureA();
			mc.fixtureB=contact->GetFixtureB();
			contactList.push_back(mc);
		}
		
		B2_NOT_USED(contact); 
	}

	/// Called when two fixtures cease to touch.
	virtual void EndContact(b2Contact* contact) 
	{ 
		MyContact mc;
		mc.fixtureA=contact->GetFixtureA();
		mc.fixtureB=contact->GetFixtureB();
		list<MyContact>::iterator pos;
		pos = find(contactList.begin(),contactList.end(),mc);
		if(pos!=contactList.end())
		{
			contactList.erase(pos);
		}
		B2_NOT_USED(contact); 
	}

	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(oldManifold);
	}

	
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(impulse);
	}
public:
	list<MyContact> contactList;
};
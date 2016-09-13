// Observer.h: interface for the Observer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBSERVER_H__8E1444BE_2F25_4EE1_AC1A_6C963256B129__INCLUDED_)
#define AFX_OBSERVER_H__8E1444BE_2F25_4EE1_AC1A_6C963256B129__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <sstream>
#include <map>

class Subject;

class Observer  
{
  friend class Subject;
public:
  // subclass must override this function to get the even handling to work;
  // pSubject - dispatched from which subject;
  // pObserverFrom - if this message is initiated from another observer, this will indicate who is it;
  // Event - the even number;
  // Data - all data related with the event number are encoded into this stringstream object;
	virtual bool Update(Subject* pSubject, Observer* pObserverFrom, unsigned int Event, const std::stringstream& Data) = 0;

  bool HasSubject() const {return !m_E2Subjects.empty();}
  
  // observer/unobserve the Event from pSubject;
  void Observe(Subject* pSubject, unsigned int Event);
  void UnObserve(Subject* pSubject, unsigned int Event);

protected:
	
	Observer();
	virtual ~Observer();
  Observer(const Observer& rhs);
  Observer& operator=(const Observer& rhs);

  // call subject to notify other observers;
  void NotifySubject(unsigned int Event, const std::stringstream& Data);

  // clear out all the subject/observer relationship;
  void ClearSubjects();

private:
  // remove the pSubject for this Observer;
  void RemoveSubject(Subject* pSubject);
  // refer to the subject object;
  typedef std::multimap<unsigned int, Subject*> E2S;  
  typedef std::pair<unsigned int, Subject*> ESPair;  
  typedef E2S::iterator ESI;
  typedef std::pair<ESI, ESI> ESPairI;
 
  E2S m_E2Subjects;
};

#endif // !defined(AFX_OBSERVER_H__8E1444BE_2F25_4EE1_AC1A_6C963256B129__INCLUDED_)

// Subject.h: interface for the Subject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUBJECT_H__8F429A5F_6BFF_48FB_8E63_5D91105ABBFC__INCLUDED_)
#define AFX_SUBJECT_H__8F429A5F_6BFF_48FB_8E63_5D91105ABBFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <sstream>
#include <map>

class Observer;

// Implement the Subject class for the Observer pattern;
class Subject  
{
  friend class Observer;
public:
  typedef std::multimap<unsigned int, Observer*> E2O;
  typedef std::pair<unsigned int, Observer*> EOPair;
  typedef E2O::iterator EOI;
  typedef std::pair<EOI, EOI> EOPairI;

  // Notify all observers in this subject, pObserverFrom is the one who generated the event;
  void Notify(Observer* pObserverFrom, unsigned int Event, const std::stringstream& Data);

protected:
  Subject();
  virtual ~Subject();
  Subject(const Subject& rhs);
  Subject& operator=(const Subject& rhs);

  // clear out all the subject/observer relationship;
  void ClearObservers();
  //Get Observer count
  int GetObserverCount() ;
private:
  // Attach/Detach the pObserver to this subject;
  void AttachObserver(Observer* pObserver, unsigned int Event);
  void DetachObserver(Observer* pObserver, unsigned int Event);
  // detatch all EO pair that matches the pObbserver;
  void DetachObserver(Observer* pObserver);
  // determine if the pObserver has any event registered with this subject;
  bool IsObserverRegistered(Observer* pObserver);

private:
  //ACE_Thread_Mutex m_Mutex;
  // The Event to Observer container;
  E2O m_Observers;
};

#endif // !defined(AFX_SUBJECT_H__8F429A5F_6BFF_48FB_8E63_5D91105ABBFC__INCLUDED_)

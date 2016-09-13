// Observer.cpp: implementation of the Observer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Observer.h"
#include "Subject.h"

Observer::Observer()
{
}

Observer::~Observer()
{
  ClearSubjects();
}

void Observer::ClearSubjects()
{
  E2S::iterator E2SI = m_E2Subjects.begin();
  while(E2SI != m_E2Subjects.end())
  {
    Subject* pSubject = (E2SI->second );
    pSubject->DetachObserver(this);
    E2SI = m_E2Subjects.begin();
  }
  m_E2Subjects.clear();
 
}

void Observer::NotifySubject(unsigned int Event, const std::stringstream& Data)
{
  ESPairI subjects = m_E2Subjects.equal_range(Event);
  ESI esi = subjects.first;
  while(esi != subjects.second)
  {
    Subject* pSubject = esi->second;
    pSubject->Notify(this,Event,Data);
    ++esi;
  }
  
}



void Observer::RemoveSubject(Subject* pSubject)
{
  ESI esi = m_E2Subjects.begin();
  for(; esi != m_E2Subjects.end();)
  {
    if(esi->second == pSubject)
    {
      esi = m_E2Subjects.erase(esi);
    }
    else
    {
      esi ++;
    }
  }
  
}

void Observer::Observe(Subject* pSubject, unsigned int Event)
{
  m_E2Subjects.insert(ESPair(Event, pSubject));
  pSubject->AttachObserver(this, Event);
  //m_bOnUpdating = false;
}

void Observer::UnObserve(Subject* pSubject, unsigned int Event)
{
  pSubject->DetachObserver(this, Event);
}

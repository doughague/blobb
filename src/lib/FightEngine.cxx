/** \file      FightEngine.cxx 
    \brief     Source for FightEngine 
    \author    John D. Hague
    \date      08.06.2014
    \copyright See License.txt
*/
#include "blobb/FightEngine.hh"        // this class

namespace Blobb {

//_____________________________________________________________________________
/** Default constructor. */
FightEngine::FightEngine(CLUI* clui, Random* random,
			 Warrior* w1, Warrior* w2)
  : mClui(clui),
    mRandom(random),
    mW1(w1),
    mW2(w2)
{
  // re-initialize fatigue to health and bleed; 
  // loss of health or fatigue per round
  w1->mFatigue.setValue(w1->mHealth.value());
  w2->mFatigue.setValue(w2->mHealth.value());
}

//_____________________________________________________________________________
/** Main method. */
Int_t FightEngine::fight()
{
  // menu
  printMenu();

  // command loop
  string cmd = readCommand();
  while(kTrue){
    // check commands
    if     (cmd=="Q" || cmd=="quit")  break;
    else if(cmd=="M" || cmd=="menu")  printMenu();
    else if(cmd=="S" || cmd=="swing") swing();
    else if(cmd=="D" || cmd=="death") death();
    else{
      mClui->os() << "Unknown command: \"" << cmd << "\"" << endl;
      printMenu();
    }
    // read next command
    cmd = readCommand();
  }

  return 0;
}

//_____________________________________________________________________________
/** Check for end-fight condition. */
Bool_t FightEngine::fightEnded() const 
{ 
  return (mW1->collapsed() || mW2->collapsed());
}
  
//_____________________________________________________________________________
/** Read (next) command. */
string FightEngine::readCommand()
{
  mClui->request("fight command");
  return mClui->readString();  
}

//_____________________________________________________________________________
/** Print command menu. */
void FightEngine::printMenu() const
{
  mClui->os() << endl;
  mClui->os() << "***********************************" << endl;
  mClui->os() << "Fight Menu (" << mW1->name() << " vs. " << mW2->name() << "):" << endl;
  mClui->os() << "\tQ|quit   Quit the fight" << endl;  
  mClui->os() << "\tM|menu   Print this menu" << endl;  
  mClui->os() << "\tS|swing  Swing-by-swing" << endl;  
  mClui->os() << "\tD|death  Death match" << endl;  
  mClui->os() << "***********************************" << endl;
}

//_____________________________________________________________________________
/** A single swing between fighters. */
void FightEngine::swing() const
{
  // --------------------------------------------
  // flight or flight
  mClui->os() << "Fight-Or-Flight ==> " << endl;
  // determine if attacking or not
  Bool_t w1forf = mW1->fightOrFlight(*mRandom); 
  mClui->os() << mW1->name() << (w1forf ? " moves to attack." : " prepares a defense.") << endl;
  Bool_t w2forf = mW2->fightOrFlight(*mRandom);
  mClui->os() << mW2->name() << (w2forf ? " moves to attack." : " prepares a defense.") << endl;
  // update disability(s) and print message
  string w1DisMsg = mW1->updateDisability(w1forf, *mRandom);
  if(w1DisMsg != "") mClui->os() << mW1->name() << w1DisMsg << endl;   
  string w2DisMsg = mW2->updateDisability(w2forf, *mRandom);
  if(w2DisMsg != "") mClui->os() << mW2->name() << w2DisMsg << endl;   

  // --------------------------------------------
  // execute "swing"
  Double_t w1bleedH(0), w2bleedH(0);
  Double_t w1bleedF(0), w2bleedF(0);
  if(!w1forf && !w2forf){
    // more fatigued if already fatigued; recover / adrenaline if not fatigued
    mClui->os() << mW1->name() << " and " << mW2->name() << " circle each other ==>" << endl;

    // w1 fatigue
    if(mW1->mFatigue.value()>50){
      mW1->mFatigue.incrValue(-3.);
      mClui->os() << mW1->name() << " regains some strength." << endl;
    }
    else {
      mW1->mFatigue.incrValue(3.);
      mClui->os() << mW1->name() << " tires slightly." << endl;
    }

    // w2 fatigue
    if(mW2->mFatigue.value()>50){
      mW2->mFatigue.incrValue(-3.);
      mClui->os() << mW2->name() << " regains some strength." << endl;
    }
    else {
      mW2->mFatigue.incrValue(3.);
      mClui->os() << mW2->name() << " tires slightly." << endl;
    }
  } // end both defending
  else {
    // if not both defending, then execute fight.
    mClui->os() << "Clash ==> " << endl;
    Double_t w1swing = mW1->swingQuality(*mRandom); 
    Double_t w2swing = mW2->swingQuality(*mRandom);
    mClui->os() << mW1->name() << ": " << w1swing << " vs " 
		<< mW2->name() << ": " << w2swing << endl;
    Double_t swingResult = w1swing - w2swing;
    mClui->os() << "swing result: " << swingResult << endl;

    // after calculating swingresult (who came out ahead in the swing), 
    // resolve damage
    if(swingResult < -100){
      mClui->os() << mW2->name() << " deals a grievous blow." << endl;
      mW1->mHealth.incrValue(-20.);
      w1bleedH += 5;
      w1bleedF += 5;
    }
    else if(swingResult < -50){
      mClui->os() << mW2->name() << " deals a serious blow." << endl;
      mW1->mHealth.incrValue (-10.);
      mW1->mFatigue.incrValue(-10.);
    }
    else if(swingResult < 50){
      mClui->os() << "Weapons clash as the warriors look for an opening." << endl;
      mW1->mFatigue.incrValue(-6.);
      mW2->mFatigue.incrValue(-6.);
    }
    else if(swingResult < 100){
      mClui->os() << mW1->name() << " deals a serious blow." << endl;
      mW2->mHealth.incrValue (-10.);
      mW2->mFatigue.incrValue(-10.);
    }
    else if(swingResult>=100){
      mClui->os() << mW1->name() << " deals a grievous blow." << endl;
      mW2->mHealth.incrValue(-20.);
      w2bleedH += 5;
      w2bleedF += 5;
    }
    else{
      // error message only
      mClui->os() << "==> An arrow fletched with human hair lands between the fighters. "
		  << "The demons are displeased and have ended the fight." 
		  << endl;
    } 
  } // end clash

  // --------------------------------------------
  // resolve bleeding
  // update warrior1 health/fatigue
  if(w1bleedH>0 || w1bleedF>0) mClui->os() << mW1->name() << " continues to bleed." << endl;
  mW1->mHealth.incrValue(-w1bleedH);
  mW1->mFatigue.incrValue(-w1bleedF);
  // update warrior2 health/fatigue
  if(w2bleedH>0 || w2bleedF>0) mClui->os() << mW2->name() << " continues to bleed." << endl;
  mW2->mHealth.incrValue(-w2bleedH);
  mW2->mFatigue.incrValue(-w2bleedF);

  // show snapshot of fight.
  mClui->os() << mW1->name() 
	      << " health: " << mW1->mHealth.value()  << "-" << w1bleedH << " per rd, " 
	      << "fatigue: " << mW1->mFatigue.value() << "-" << w1bleedF << " per rd" << endl;
  if(mW1->collapsed())
    mClui->os() << mW1->name() << " collapses. *****" << endl;

  mClui->os() << mW2->name() 
	      << " health: " << mW2->mHealth.value()  << "-" << w2bleedH << " per rd, " 
	      << "fatigue: " << mW2->mFatigue.value() << "-" << w2bleedF << " per rd" << endl;
  if(mW2->collapsed())
    mClui->os() << mW2->name() << " collapses. *****" << endl;
        
  // see if a fighter is defeated
  // update: should account for if both are defeated
  if(fightEnded()) mClui->os() << "The fight has ended. *****" << endl;
  else             mClui->os() << "Awaiting next round." << endl;
        
  // resolve disabilities
  Int_t printContents = Printable::kClassName | 
                        Printable::kName      | 
                        Printable::kTitle     | 
                        Printable::kValue     | 
                        Printable::kExtras;
  mW1->updateDisability(w1forf, *mRandom);
  mW1->printStream(mClui->os(), printContents, Printable::kSingleLine);
  mW2->updateDisability(w2forf, *mRandom);
  mW2->printStream(mClui->os(), printContents, Printable::kSingleLine);
  // mClui->os() << mW2->name() 
  // 	      << " disabilities: " << mW2->stun().value() 
  // 	      << "/" << mW2->disarm().value() 
  // 	      << "/" << mW2->fallen().value() << endl;
          
  // if(cmd == "s") { mClui->os() << "The fight rages on. Choose s to continue. *****" << endl; cmd = "m"; }
  mClui->os() << endl;
}

//_____________________________________________________________________________
/** A death match between fighters. */
void FightEngine::death() const
{
  while(!fightEnded())
    swing();
}

} // end namespace Blobb

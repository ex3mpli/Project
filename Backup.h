

class Engine
{
  public:
         void backup();
         static Weapon* GetOldWeaponByIndex(int index)
	       {
		       return Engine::old_weapons_[index];
	       }
    
  private:
          static Weapon *old_weapons_[2000];
          
          Weapon **weapons_;
};

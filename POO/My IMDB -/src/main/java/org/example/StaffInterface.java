package org.example;

public interface StaffInterface {
    public void addProductionSystem(Production p);
    public void addActorSystem(Actor a);
    public void removeProductionSystem(Production p);
    public void removeActorSystem(Actor a);
    public void updateProduction(Production p);
    public void updateActor(Actor a);
}

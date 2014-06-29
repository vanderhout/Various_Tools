/*
This class traces the outline of some square-tile-based room, only stepping where a given condition is satisfied
Upon hitting a wall, it will turn to its left
*/
class Tracer
{
  //Location of the tracer
  private int x, y;
  public int x(){return x;}
  public int y(){return y;}
  //Directions: 0 1 2 3 = UP DOWN LEFT RIGHT
  private int direction;
  
  /*
  startX, startY - starting coordinates
  startDirection - direction to initially keep travelling until a wall is hit
  If you do not start inside a valid square, it will keep travelling in this direction, until hitting a valid square.
  If there are no valid squares, exception!
  One the constructor is finished, the tracer should be in its first valid square
  */
  public Tracer(int startX, int startY, int startDirection){
    x=startX;
    y=startY;
    direction=startDirection;
    
    if(direction<0 || 3<direction){
      println("ERROR: INVALID DIRECTION!");
      int abc=1/0;
    }
    
    //Not in room, keep wandering.
    while(!IsInRoom())Step();
    
    //If your next step still is in the room, keep going.
    while(StepIsInRoom())Step();
  }
  
  /*
  Are these coordinates part of the room?
  */
  private boolean IsInRoom(int myX, int myY){
    //TO IMPLEMENT
  }
  
  private boolean IsInRoom(){
    return IsInRoom(x, y);
  }
  
  private boolean StepIsInRoom(){
    switch(direction){
      case 0:
      return IsInRoom(x, y-1);
      case 1:
      return IsInRoom(x, y+1);
      case 2:
      return IsInRoom(x-1, y);
      case 3:
      return IsInRoom(x+1, y);
    }
    println("ERROR: INVALID DIRECTION!");
    int abc=1/0;
    return false;
  }
  
  /*
  Take a step in the direction
  */
  private void Step(){
    switch(direction){
      case 0:
      y--;
      break;
      case 1:
      y++;
      break;
      case 2:
      x--;
      break;
      case 3:
      x++;
      break;
    }
  }
  
  /*
  Tracer starts off facing a wall, turns left
  Tracer ends facing in a new position facing a new wall
  If there is no new position, return false
  */
  public boolean PerformTraceStep(){
    if(StepIsInRoom()){
      println("ERROR: NOT FACING WALL!");
      int abc=1/0;
    }
    
    for(int i=0;i<3;i++){
    TurnLeft();
    if(StepIsInRoom()){
      Step();
      TurnRight();
      if(StepIsInRoom()){
        Step();
        TurnRight();
      }
      return true;
    }
    }
    
    return false;
    
  }
  
  /*
  Change direction to rotate to its left
  */
  private void TurnLeft(){
    switch(direction){
      case 0:
      direction=2;
      break;
      case 1:
      direction=3;
      break;
      case 2:
      direction=1;
      break;
      case 3:
      direction=0;
      break;
    }
  }
  
  /*
  Change direction to rotate to its right
  */
  private void TurnRight(){
    switch(direction){
      case 0:
      direction=3;
      break;
      case 1:
      direction=2;
      break;
      case 2:
      direction=0;
      break;
      case 3:
      direction=1;
      break;
    }
  }
}

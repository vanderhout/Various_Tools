PrintWriter gradFunc;
PrintWriter grads;

void setup() {
  size(130,16);
  noLoop();
  
}


ArrayList filesToArrayList() {
  ArrayList<File> filesList = new ArrayList<File>();
  String folderPath = "/Users/russellvanderhout/Documents/Processing/GradientRipper/";//selectFolder();
  if (folderPath != null) {
    File file = new File(folderPath);
    File[] files = file.listFiles();
    for (int i = 0; i < files.length; i++) {
      filesList.add(files[i]);
    }
  }
  return(filesList);
}



void draw() {
  int count=0;
  gradFunc=createWriter("gradFunc.txt");
  grads=createWriter("grads.txt");
  
  gradFunc.println("void randGrad(){");
  gradFunc.println("  Random ran;");
  gradFunc.println("  int num=ran.nextInt(12345);");

  ArrayList<File> filesList = filesToArrayList();
  for(File f : filesList){
    String name=f.getName();
    if(name.charAt(name.length()-1)=='f'){
      String vname=name.substring(0, name.length()-4);
      /*
      gradFunc.println("if(num=="+count+"){");
      gradFunc.println("  for(int i=0;i<130;i++)");
      gradFunc.println("  gradient[i]="+vname+"[i];");
      gradFunc.println("}else ");
      */
      PImage img;
      img = loadImage(name);
      image(img, 0, 0);
      //grads.println("static final int[] "+vname+"=new int[]{");
      
      grads.print("{");
      for(int i=0;i<129;i++){
        grads.print(get(i,8)&((255<<16)+(255<<8)+255)); 
        grads.print(", "); 
      }
        grads.print(get(129,8)&((255<<16)+(255<<8)+255)); 
        grads.print("},\n\n"); 
      
      
      count++;
    }
  }
  gradFunc.flush(); // Writes the remaining data to the file
  gradFunc.close(); // Finishes the file
  grads.flush(); // Writes the remaining data to the file
  grads.close(); // Finishes the file
}

int level=1;
int C=0;  //csae 0:stop 1:up 2:down
int up[5]={0};
int down[5]={0};
int s[5]={0}; //stop level
int I=0;


void setup() {
  pinMode(2, INPUT);	//up
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  
  pinMode(8, INPUT);	//down
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT); 
  
  analogWrite(A1,0);
  analogWrite(A2,0);
  analogWrite(A3,0);
  analogWrite(A4,0);
  analogWrite(A5,0);
}

void loop() {
  set();  //開關是否按
  check();  //電梯up down stop
  link();  //先後順序
}


void set()
{
  for(I=0;I<=4;I++)
  {
    if(digitalRead(I+2)==HIGH)
    {
      up[I]=1;
      s[I]=1;
    }
  }
  for(I=5;I<=9;I++)
  {
    if(digitalRead(I+3)==HIGH)
    {
      down[I-5]=1;
      s[I-5]=1;
    }
  }
}

void check()
{
  for(I=0;I<=4;I++)
  {
    if(s[I]==1 && C==0)  //電梯停止 
    {
      if(level==I+1)
      {
        analogWrite(I+15,255); //開門
        
        s[I]=0;
        up[I]=0;
        down[I]=0;
        C=0;
        
        
        delay(3000);
        set();
        
        analogWrite(I+15,0); //關門
      }
      else if(level<I+1)
      {
        C=1; //up
      }
      else
      {
        C=2; //down
      }
    } 
  }
}

void link()
{
  if(C==1)
  {
    analogWrite(level+14,255);
    delay(1500);
    analogWrite(level+14,0);
    level+=1;
    analogWrite(level+14,255);
    
    set();
    
    if(s[level-1]==1)
    {
      boolean S=false;//check stop
      boolean CU=false;//check up
      
       for(I=level;I<=4;I++) //確定上層 有無要up
      {
        if(up[I]==1)
        {
          CU=true;
        }
      }
      
      if(up[level-1]==1) //本層按up
      {
        up[level-1]=0;
        s[level-1]=0;
        delay(1500);
        analogWrite(level+14,0);
        
        set();
      }
      else if(down[level-1]==1 && CU==false) //本層按down 且上層無up
      {
        int K=-1; //確認最大樓層
        for(int J=level-1;J<=4;J++)
        {
          if(down[J]==1)
          {
            K=J; //確定最大樓層按的 down
          }
        }
        if(level-1==K) //確定本層為最大樓層要down
        {
          down[level-1]=0;
          s[level-1]=0;
          delay(1500);
          analogWrite(level+14,0);
          
          set();
        }
      }
      
      if(down[level-1]==1) // 本層要down
      {
        s[level-1]=1;
      }
      
      
      for(I=level-1;I<=4;I++)
      {
        if(s[I]==1)
        {
          S=true;
        }
      }
      
      if(S==false)
      {
        C=0;
      }
      
    }
    
  }
  
  
  //**************************************
  
  
  else if(C==2)
  {
    analogWrite(level+14,255);
    delay(1500);
    analogWrite(level+14,0);
    level-=1;
    analogWrite(level+14,255);
    
    set();
    
    if(s[level-1]==1)
    {
      boolean S=false;
      boolean CD=false; //check down
      
      for(I=level-1;I>=0;I--)
      {
        if(down[I]==1)
        {
          CD=true;
        }
      }
      
      if(down[level-1]==1)
      {
        down[level-1]=0;
        s[level-1]=0;
        delay(1500);
        analogWrite(level+14,0);
        
        set();
      }
      else if(up[level-1]==1 && CD==false)
      {
        int K=5; //確認最小樓層
        for(int J=level-1;J>=0;J--)
        {
          if(up[J]==1)
          {
            K=J; //確定最小樓層按的 up
          }
        }
        if(level-1==K) //確定本層為最小樓層要up
        {
          up[level-1]=0;
          s[level-1]=0;
          delay(1500);
          analogWrite(level+14,0);
          
          set();
        }
      }
      
      if(up[level-1]==1)
      {
        s[level-1]==1;
      }
      
      for(I=level-1;I>=0;I--)
      {
        if(s[I]==1)
        {
          S=true;
        }
      }
      
      if(S==false)
      {
        C=0;
      }
      
    }
    
  }
  
  
}











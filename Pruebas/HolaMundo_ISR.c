bit flag;

#pragma interrupt_handler ISR

void ISR(void)
{
   flag=1;
}

void main()
{
   --
   --
   while(1)
   {
      --
      --
      /* Wait for the ISR to set the
      * flag; reset it before
      * taking any action. */
      if (flag)
      {
         flag = 0;
         /* Perform the required action here */
      }
   }
}

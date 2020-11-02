# LAoE-keypad-display-interface
Readers of Learning the Art of Electronics (A Hands-On Lab Course by Thomas C. Hayes, Cambridge University Press) will have discovered nearly halfway through that, to continue with the labs, access to two pieces of equipment is required: a keypad and a display. Costing around $150 each it appears that neither are available outside the US. On the authors’ website are some details of the specialised boards and a hint that some may like to make their own. Both use dedicated microprocessors and, apart from a sense that this is really cheating (they seem to use the same chips that are used in the labs), the code to run on them is not available. So, I decided to make my own. I have as far as reasonably practicable duplicated all the functions of both boards with the notable exception of the programming options for the Silicon Labs ‘8051 and Xilinx ‘9572, since I intend to program these on development boards, readily (and cheaply) available on eBay (see later for minor modification needed). From the published photographs, limited descriptions, old documents, and a fair amount of breadboard testing together with Arduino IDE coding I managed to replicate both boards. Prototype PCBs were manufactured and tested. Each board measured 150mm x 100mm and used only easily available and mainly very cheap through-hole components. The boards used a nominal 5V supply so external level shifters would be required for any attached 3.3V devices (not the Xilinx boards I am using since all I/O pins are 5V tolerant). I am using development boards in the labs and they have their own supplies and built-in voltage regulators. The total material cost was under £50. A significant amount of testing and recoding as well as continuing with the book to discover what these devices were being used for enabled some changes and simplifications to be made. Both the keypad and display now occupy a single PCB with fewer components and obviously no external connections between them. The number keypad is connected via an 8-pin header and fixed to the PCB with M2 stand-offs. The LCD also uses headers and stand-offs (M3) for connections and fixing (see later for necessary and optional modifications). The new board uses two Arduino Nano’s which can be (re)programmed in-situ from their own Mini-B USB jacks. In use they are powered from the board – no external connections are required except when programming.
The official board documentation notes that two 8-bit transparent latches are normally held in transparent mode so, I presume, are rarely used. I opted for an off-board solution using two 74HC573 IC’s and have also designed a separate PCB to implement this feature. It has two separate latch-enable inputs and a switch to combine them and is easily connected to any bus that needs latching.
The book’s chapters on building the ‘computer’ add a few features that seem rightfully placed with the keypad, so I have incorporated these on the board. They are:

•	The additional KD8 and KD9 inputs via DIP switches

•	The SYNCLOAD* and RST* functions via DIP switches

•	The LOAD* function via a momentary pushbutton


Keypad functions

The keypad allows entry of an 8-bit hexadecimal number (MSB first) from two key presses for output to the keypad data bus. The entered number is displayed live on the LCD in both hexadecimal and binary. As with the ‘official’ board it also provides control signals via three slide switches and five pushbuttons generating the six output signals. The pushbuttons are hardware debounced and the keypad itself is debounced in software through the Keypad.h library (by Mark Stanley and Alexander Brevig). There is an additional ‘clear’ button which sets the output to a high impedance state (indicated on the LCD). The control slide switches have bi-colour LEDs to indicate status (Green=LOW asserted, Red=HIGH asserted). Frequency is selected by a switch instead of the original’s jumper and is also displayed on the LCD. 


Display functions

All information is displayed on a 20-column x 4-row LCD driven using the I2C protocol via a Serial Interface Module (backpack), both readily available on eBay.

Inputs: 	The board can take in 32 lines of external data (normally 16 for the address bus, 8 for the data bus and 8 for the keypad) for display.

Display:	The external 32 bits are displayed in binary and hexadecimal on four lines with titles indicating the source (Address, Data, and Input) and unlike the original there is no switching or multiplexing necessary.


Connections

Power is via a centre positive barrel jack. All signal connections are made via IDC connectors. The IDC connectors can be replaced by either male or female header pins.

•	IDC 1 takes the 16 address lines

•	IDC 2 takes the 8 data lines and 8 keypad lines

•	IDC 3 takes all the control signals


LCD and I2C Serial Interface Module modifications

Get an LCD without the backpack fitted or desolder it. Straighten or replace the 2-pin and 4-pin right-angled headers on the backpack with straight header pins on the same side (these then connect directly to the PCB and provide the mechanical and electrical connections). Remove, if present or are male pins, the 16-pin header on the LCD and replace with female headers on the same side (this then fits onto the backpack header). The standard off-the-shelf I2C backpack has a trimpot for contrast adjustment but keeping this raises the LCD. The PCB has a hole for access, but I have also provided space for this trimpot on top of the PCB – just remove the existing trimpot and hardwire to the new location through the hole. Power can be connected from the existing GND and VCC points so only the wiper needs to be brought through the hole. Doing this avoids having to turn over the whole board to adjust the contrast. The backpack also has an option for brightness control and a second trimpot with a transistor can be added without additional wiring as links are made on PCB traces. If not fitted the bottom trimpot pads or the 2-pin header on the baclpack need to be bridged with a link replacing the jumper.


Xilinx CPLD board modification

The board shown in 'Xilinx CPLD board.png' is the one I’m using for the labs (two are needed), programmed using the Xilinx Platform Cable USB with iMPACT (part of the Xilinx ISE suite). All the IO pins are needed for the labs and all are broken out to headers on the board except P1 (labelled CLK on the board) which is instead linked to the on-board 50MHz crystal. This is easily fixed by removing the 0Ω resistor labelled R9 on the rear of the board. 

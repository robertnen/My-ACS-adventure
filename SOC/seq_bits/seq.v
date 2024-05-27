`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/22/2024 10:35:12 AM
// Design Name: 
// Module Name: seq
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module seq();
    reg clk, reset, bin;
    wire bout;
    
    seq_bit sb(clk, reset, bin, bout);
    
    always
        #10 clk = ~clk;
        
    initial begin
        reset = 1; clk = 0;
        #20 reset = 0; bin = 1;
        #20 bin = 0;
        #20 bin = 0;
        #20 bin = 1;
      end
endmodule

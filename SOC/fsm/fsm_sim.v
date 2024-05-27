`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/03/2024 11:28:02 AM
// Design Name: 
// Module Name: fsm_sim
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


module fsm_sim();

reg clk, reset, B1, B2, B3;
wire EB, EB1, EB2;

fsm_ aparat(clk, reset, B1, B2, B3, EB, EB1, EB2);

always
#10 clk = ~clk;

initial begin
    reset = 1; clk = 0;
    #20 reset = 0; B1 = 0; B2 = 0; B3 = 1;
    #40 B3 = 0;
end

endmodule

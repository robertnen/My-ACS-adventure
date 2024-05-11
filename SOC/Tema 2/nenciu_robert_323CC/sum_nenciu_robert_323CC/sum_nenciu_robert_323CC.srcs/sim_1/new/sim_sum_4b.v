`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/10/2024 11:37:32 AM
// Design Name: 
// Module Name: sim_sum_4b
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


module sim_sum_4b();
    reg[3:0] a, b;
    reg c_in;
    wire[3:0] sum;
    wire c_out;
    
    sum_4b sumator(a, b, c_in, sum, c_out);
    
    initial begin
        a = 3; b = 4;
        c_in = 0;
    end
endmodule

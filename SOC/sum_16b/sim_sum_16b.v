`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/17/2024 10:58:43 AM
// Design Name: 
// Module Name: sim_sum_16b
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


module sim_sum_16b();
    reg[15:0] a, b;
    reg c_in;
    wire[15:0] sum;
    wire c_out;

    sum_16b sumator(a, b, c_in, sum, c_out);
    
    initial begin
        a = 16'b1000100010001000; b = 16'b1000100010001000;
        c_in = 0;
    end
    
endmodule

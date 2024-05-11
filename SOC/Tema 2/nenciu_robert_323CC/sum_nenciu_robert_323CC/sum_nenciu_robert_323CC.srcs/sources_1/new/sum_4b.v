`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/10/2024 11:24:16 AM
// Design Name: 
// Module Name: sum_4b
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


module sum_4b(
    input[3:0] a, b,
    input c_in,
    output[3:0] sum,
    output c_out);
    
    wire g_0, g_1, g_2, g_3, p_0, p_1, p_2, p_3, c_1, c_2, c_3, c_4;
    
    assign g_0 = a[0] & b[0];
    assign g_1 = a[1] & b[1];
    assign g_2 = a[2] & b[2];
    assign g_3 = a[3] & b[3];
    
    assign p_0 = a[0] | b[0];
    assign p_1 = a[1] | b[1];
    assign p_2 = a[2] | b[2];
    assign p_3 = a[3] | b[3];
    
    assign c_1 = g_0 | (p_0 & c_in);
    assign c_2 = g_1 | (p_1 & g_0) | (p_1 & p_0 & c_in);
    assign c_3 = g_2 | (p_2 & g_1) | (p_2 & p_1 & g_0) | (p_2 & p_1 & p_0 & c_in);
    assign c_4 = g_3 | (p_3 & g_2) | (p_3 & p_2 & g_1) | (p_3 & p_2 & p_1 & g_0) | (p_3 & p_2 & p_1 & p_0 & c_in);
    
    assign c_out = c_4;
    
    assign sum[0] = a[0] ^ b[0] ^ c_in;
    assign sum[1] = a[1] ^ b[1] ^ c_1;
    assign sum[2] = a[2] ^ b[2] ^ c_2;
    assign sum[3] = a[3] ^ b[3] ^ c_3;
endmodule

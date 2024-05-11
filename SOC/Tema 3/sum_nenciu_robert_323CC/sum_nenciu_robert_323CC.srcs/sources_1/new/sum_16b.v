`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/17/2024 10:56:28 AM
// Design Name: 
// Module Name: sum_16b
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


module sum_16b(
    input[15:0] a, b,
    input c_in,
    output[15:0] sum,
    output c_out
    );

    wire P_0, P_1, P_2, P_3, G_0, G_1, G_2, G_3;
    wire c_1, c_2, c_3;
    
    sum_4b sumator_1(a[3:0], b[3:0], c_in, sum[3:0], P_0, G_0);
    
    assign c_1 = P_0 | G_0 & c_in;
    
    sum_4b sumator_2(a[7:4], b[7:4], c_1, sum[7:4], P_1, G_1);
    
    assign c_2 = G_1 | (P_1 & G_0) | (P_1 & P_0 & c_in);
    
    sum_4b sumator_3(a[11:8], b[11:8], c_2, sum[11:8], P_2, G_2);
    
    assign c_3 = G_2 | (P_2 & G_1) | (P_2 & P_1 & G_0) | (P_2 & P_1 & P_0 & c_in);
    
    sum_4b sumator_4(a[15:12], b[15:12], c_3, sum[15:12], P_3, G_3);

    assign c_out = G_3 | (P_3 & G_2) | (P_3 & P_2 & G_1) | (P_3 & P_2 & P_1 & G_0) | (P_3 & P_2 & P_1 & P_0 & c_in);
endmodule

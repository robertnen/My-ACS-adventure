`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/22/2024 10:25:46 AM
// Design Name: 
// Module Name: seq_bit
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


module seq_bit(clk, reset, bin, bout);

input clk, reset, bin;
output reg bout;

reg[1:0] state, next;

always @(posedge clk)
   if (reset) begin
      state = 0;
      bout = 0;
   end else state <= next;

always @(state, bin)
    case(state)
        2'b00: // am 0 in sir
            if(bin == 1) begin
                next = 2'b01;
                bout = 0;
            end else next = 2'b00;
        2'b01: // am 1 in sir
            if(bin == 0) begin
                next = 2'b11;
                bout = 0;
            end else begin next = 2'b01; bout = 0; end
        2'b11: // am 10 in sir
            if(bin == 1) begin
                next = 2'b01;
                bout = 0;
            end else if(bin == 0) begin
                        next = 2'b10;
                        bout = 0;
                     end
        2'b10: // am 100 in sir
            if(bin == 0) begin
                next = 2'b00;
                bout = 0;
            end else if(bin == 1) begin
                        next = 2'b00;
                        bout = 1;
                     end
        default:
            begin
                next = 0;
                bout = 0;
            end
    endcase
endmodule

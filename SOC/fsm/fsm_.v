`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/03/2024 11:00:10 AM
// Design Name: 
// Module Name: fsm_
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


module fsm_(clk, reset, B1, B2, B3, EB, EB1, EB2);

input clk, reset, B1, B2, B3;
output reg EB, EB1, EB2;

reg[2:0] state, next;

always @(posedge clk)
    if(reset) begin
        state <= 0;
        EB <= 0;
        EB1 <= 0;
        EB2 <= 0;
    end else state <= next;
    
    always @(state, B1, B2, B3)
        case(state)
            3'b000: // am 0 lei in aparat
                if(B1 == 1 && B2 == 0 && B3 == 0) begin
                    next = 3'b001;
                    EB = 0;
                    EB1 = 0;
                    EB2 = 0;
                end else if(B1 == 0 && B2 == 1 && B3 == 0) begin
                            next = 3'b100;
                            EB = 0;
                            EB1 = 0;
                            EB2 = 0;
                         end else if(B1 == 0 && B2 == 0 && B3 == 1) begin              
                                        next = 3'b010;
                                        EB = 0;
                                        EB1 = 0;
                                        EB2 = 0;
                                     end else begin
                                        EB = 0;
                                        EB1 = 0;
                                        EB2 = 0;
                                        end
            3'b001: // am 1 leu in aparat
                if(B1 == 0 && B2 == 0 && B3 == 0) begin
                    next = 3'b000;
                    EB = 0;
                    EB1 = 1;
                    EB2 = 0;
                end else if(B1 == 1 && B2 == 0 && B3 == 0) begin
                            next = 3'b011;
                            EB = 0;
                            EB1 = 0;
                            EB2 = 0;
                         end
            3'b010: // am 10 lei in aparat
                begin
                    next = 3'b100;
                    EB = 0;
                    EB1 = 0;
                    EB2 = 1;
                end
            3'b100: // am 5 lei in aparat
                begin
                    next = 3'b011;
                    EB = 1;
                    EB1 = 0;
                    EB2 = 0;
                end
            3'b011: // am 2 lei in aparat
                if(B1 == 0 && B2 == 0 && B3 == 0) begin
                    next = 3'b001;
                    EB = 0;
                    EB1 = 1;
                    EB2 = 0;
                end else if(B1 == 1 && B2 == 0 && B3 == 0) begin
                        next = 3'b000;
                        EB = 1;
                        EB1 = 0;
                        EB2 = 0;
                    end  else begin
                            next = 3'b001;
                            EB = 0;
                            EB1 = 0;
                            EB2 = 0;
                            end
             default:
                begin
                    next = 0;
                    EB = 0;
                    EB1 = 0;
                    EB2 = 0;
                end
        endcase
endmodule

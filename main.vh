module gunshot_detection (
    input wire clk,                // System clock
    input wire reset,              // System reset
    input wire [15:0] mic_data [5:0], // 6 microphones, 16-bit data each
    output reg gunshot_detected,   // Gunshot detected flag
    output reg [2:0] direction     // Direction of gunshot (0 to 5 for each microphone)
);

    parameter THRESHOLD = 16'h0A00; // Threshold value for detection
    reg [15:0] mic_data_filtered [5:0]; // Filtered microphone data
    reg [15:0] max_value;
    reg [2:0] max_index;

    integer i;

    // Filtering and Detection Process
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            gunshot_detected <= 0;
            direction <= 3'b000;
        end else begin
            max_value <= 16'h0000;
            max_index <= 3'b000;

            for (i = 0; i < 6; i = i + 1) begin
                // Simulate bandpass filtering (placeholder for actual filter logic)
                mic_data_filtered[i] <= (mic_data[i] > THRESHOLD) ? mic_data[i] : 16'h0000;

                // Gunshot detection
                if (mic_data_filtered[i] > max_value) begin
                    max_value <= mic_data_filtered[i];
                    max_index <= i[2:0];
                end
            end

            // If any of the filtered data exceeds the threshold, detect gunshot
            if (max_value > THRESHOLD) begin
                gunshot_detected <= 1;
                direction <= max_index;
            end else begin
                gunshot_detected <= 0;
                direction <= 3'b000;
            end
        end
    end
endmodule

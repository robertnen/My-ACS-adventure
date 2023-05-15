function [J, grad] = cost_function(params, X, y, lambda, ...
                   input_layer_size, hidden_layer_size, ...
                   output_layer_size)

  [n, ~] = size(params);
  h = hidden_layer_size;
  i = input_layer_size;
  o = output_layer_size;

  Theta1 = reshape(params(1 : h * (i + 1)), h, i + 1);
  Theta2 = reshape(params(h * (i + 1) + 1 : n), o, h + 1);

  s1 = sum(sum(Theta1 .^ 2));
  s2 = sum(sum(Theta2 .^ 2));

  [X1, X2, y1, y2] = split_dataset(X, y, 0.5);

  % TODO2: Forward propagation
  
  % TODO3: Compute the error in the output layer and perform backpropagation
  
  % TODO4: Determine the gradients
  
  % TODO5: Final J and grad

endfunction

%checker Tema2 MN
  total_points = 0;
  no_tests = 4;
  no_pcs = 2;
  no_train_images = 10000;
  err = 10^-2;
  addpath ('functions/');
  
  printf('---------------------------------------------------------------------------------------------------------\n');
	printf('---------------------------------------------------------------------------------------------------------\n');
	printf('------------------------------------------ Testare Tema 1 MN --------------------------------------------\n');
	printf('---------------------------------------------------------------------------------------------------------\n');
	printf('---------------------------------------------------------------------------------------------------------\n');
  
  im = "image";
  pcs = [3, 30];
  
  %%% -----------------------------------------------------------
  %%% Test Task 1
  %%% -----------------------------------------------------------
  printf ('---------------------------------------------------------------------------------------------------------\n');
  printf ('-------------------------------------------------Task 1--------------------------------------------------\n');
  task1_points = 0;
  
    for i = 1:no_tests
      for j = 1:no_pcs
        % Creare nume fisiere de intrare si de referinta
        name = strcat (im, num2str (i));
        image_ref = strcat ('ref/task1_', name); 
        image_ref = strcat (image_ref, '_');
        image_ref = strcat (image_ref, num2str (pcs(j)));
        image_ref = strcat (image_ref, '.gif');
        image_in = strcat ('in/', name);
        image_in = strcat (image_in, '.gif');
    
        image_ref_mat = imread (image_ref);
        image_in_mat = imread (image_in);
        image_result_mat = task1 (image_in_mat, pcs(j));
    
        success = 1;
        [m, n] = size (image_ref_mat);
        for k = 1:m
          for l = 1:n
            if abs (image_ref_mat(k,l) - image_result_mat(k,l)) > err
              success = 0;
              break;
            endif
          endfor
          if success == 0
            break;
          endif
        endfor
    
        if success == 0
          printf ('Task 1 - image %d - %d PCs .....................................................Incorect [%d / %d]\n' , i, pcs(j), 0, 2.5);
        else
          printf ('Task 1 - image %d - %d PCs .....................................................Corect [%d / %d]\n' , i, pcs(j), 2.5, 2.5);
          task1_points += 2.5;
          total_points += 2.5;
        endif
      endfor
    endfor
 
  printf ('Task 1 = [%d / 20]\n', task1_points);
  
  %%% -----------------------------------------------------------
  %%% Test Task 2
  %%% -----------------------------------------------------------
  printf ('---------------------------------------------------------------------------------------------------------\n');
  printf ('-------------------------------------------------Task 2--------------------------------------------------\n');
  task2_points = 0;
  
    for i = 1:no_tests
      for j = 1:no_pcs
        % Creare nume fisiere de intrare si de referinta
        name = strcat (im, num2str (i));
        image_ref = strcat ('ref/task2_', name); 
        image_ref = strcat (image_ref, '_');
        image_ref = strcat (image_ref, num2str (pcs(j)));
        image_ref = strcat (image_ref, '.gif');
        image_in = strcat ('in/', name);
        image_in = strcat (image_in, '.gif');
    
        image_ref_mat = imread (image_ref);
        image_in_mat = imread (image_in);
        image_result_mat = task2 (image_in_mat, pcs(j));
    
        success = 1;
        [m, n] = size (image_ref_mat);
        for k = 1:m
          for l = 1:n
            if abs (image_ref_mat(k,l) - image_result_mat(k,l)) > err
              success = 0;
              break;
            endif
          endfor
          if success == 0
            break;
          endif
        endfor
    
        if success == 0
          printf ('Task 2 - image %d - %d PCs .....................................................Incorect [%d / %d]\n' , i, pcs(j), 0, 2.5);
        else
          printf ('Task 2 - image %d - %d PCs .....................................................Corect [%d / %d]\n' , i, pcs(j), 2.5, 2.5);
          task2_points += 2.5;
          total_points += 2.5;
        endif
      endfor
    endfor
 
  printf ('Task 2 = [%d / 20]\n', task2_points);
  
  %%% -----------------------------------------------------------
  %%% Test Task 3
  %%% -----------------------------------------------------------
  printf ('---------------------------------------------------------------------------------------------------------\n');
  printf ('-------------------------------------------------Task 3--------------------------------------------------\n');
  task3_points = 0;
  
    for i = 1:no_tests
      for j = 1:no_pcs
        % Creare nume fisiere de intrare si de referinta
        name = strcat (im, num2str (i));
        image_ref = strcat ('ref/task3_', name); 
        image_ref = strcat (image_ref, '_');
        image_ref = strcat (image_ref, num2str (pcs(j)));
        image_ref = strcat (image_ref, '.gif');
        image_in = strcat ('in/', name);
        image_in = strcat (image_in, '.gif');
    
        image_ref_mat = imread (image_ref);
        image_in_mat = imread (image_in);
        image_result_mat = task3 (image_in_mat, pcs(j));
    
        success = 1;
        [m, n] = size (image_ref_mat);
        for k = 1:m
          for l = 1:n
            if abs (image_ref_mat(k,l) - image_result_mat(k,l)) > err
              success = 0;
              break;
            endif
          endfor
          if success == 0
            break;
          endif
        endfor
    
        if success == 0
          printf ('Task 3 - image %d - %d PCs .....................................................Incorect [%d / %d]\n' , i, pcs(j), 0, 2.5);
        else
          printf ('Task 3 - image %d - %d PCs .....................................................Corect [%d / %d]\n' , i, pcs(j), 2.5, 2.5);
          task3_points += 2.5;
          total_points += 2.5;
        endif
      endfor
    endfor
 
  printf ('Task 3 = [%d / 20]\n', task3_points);
    
  %%% -----------------------------------------------------------
  %%% Test Task 4
  %%% -----------------------------------------------------------
  printf ('---------------------------------------------------------------------------------------------------------\n');
  printf ('-------------------------------------------------Task 4--------------------------------------------------\n');
  task4_points = 0;
  random_photos = [1431, 2327, 5264, 6774, 8390];
  
  % Pregatirea datelor de antrenament.
  [train_mat, train_val] = prepare_data ('mnist.mat', no_train_images);
  [new_train_mat, miu, F, Vk] = magic_with_pca (train_mat, 23);
    
  name = 'Digit Recognition - ref/DR_';
  name_in = 'Digit Recognition - in/image';
  for i = 1:2
    test_name = strcat (name, num2str (i));
    test_name = strcat (test_name, '_');
    if i == 1
      train = train_mat;
    else
      train = new_train_mat;
    endif
    for j = 1:5
      image_ref = strcat (test_name, num2str (j));
      image_ref = strcat (image_ref, '.png');
      
      im = visualise_image (train, random_photos (j));
      im_ref = imread (image_ref);
      
      % Transformama im si im_ref in double pt a se face corect calculul.
      im = double (im);
      im_ref = double (im_ref);
    
      [m, n] = size(im);
      [p, q] = size (im_ref);
      if m != p || n != q
        success = 0;
      else
        success = 1;
        for k = 1:28
          for l = 1:28
            if abs (im (k,l) - im_ref (k,l)) > err
              success = 0;
             break;
            endif
         endfor
         if success == 0
           break;
         endif
       endfor
     endif
      
     if success == 0
       if i == 1
        printf ('Task 4 - data image %d ..............................................................Incorect [%d / %d]\n' , j, 0, 2);
       else
        printf ('Task 4 - data processing image %d ...................................................Incorect [%d / %d]\n' , j, 0, 1);
      endif
     else
       if i == 1
        printf ('Task 4 - data image %d .............................................................Corect [%d / %d]\n' , j, 2, 2);
        task4_points += 2;
        total_points += 2;
       else
        printf ('Task 4 - data processing image %d ..................................................Corect [%d / %d]\n' , j, 1, 1);
        task4_points += 1;
        total_points += 1;
      endif
     endif
   endfor
 endfor
 
  for i = 1:2
   test_name = strcat (name, num2str (i + 2));
   test_name = strcat (test_name, '_');
   for j = 1:10
     image_in = strcat (name_in, num2str (j));
     image_in = strcat (image_in, '.png');
     image_ref = strcat (test_name, num2str (j));
     image_ref = strcat (image_ref, '.txt');
     
     im = imread (image_in);
     im = prepare_photo (im);
     
     if i == 2
      im = classifyImage (im, train_mat, train_val, 23);
     endif
     
     [m, n] = size (im);
     
     ref = dlmread (image_ref);
     success = 1;
     for k = 1:n
       if im (k) != ref (k)
         success = 0;
         break;
       endif
     endfor
     
     if success == 0
       if i == 1
         printf ('Task 4 - invert image %d .....................................................Incorect [%d / %d]\n' , j, 0, 0.5 * i);
       else
         printf ('Task 4 - prediction %d ..........................................................Incorect [%d / %d]\n' , j, 0, 1.5);
       endif
     else
       if i == 1
         printf ('Task 4 - invert image %d .....................................................Corect [%d / %d]\n' , j, 0.5 * i, 0.5 * i);
         task4_points += 0.5 * i;
         total_points += 0.5 * i;
       else
         printf ('Task 4 - prediction %d ..........................................................Corect [%d / %d]\n' , j, 1.5, 1.5);
         task4_points += 1.5;
         total_points += 1.5;
       endif
     endif
   endfor
  endfor
  printf ('Task 4 = [%d / 35]\n', task4_points);
  
  %%% -----------------------------------------------------------
  %%% Test Readme
  %%% -----------------------------------------------------------
  
  printf ('---------------------------------------------------------------------------------------------------------\n');
  printf ('---------------------------------------------------------------------------------------------------------\n');
  if exist('Readme.pdf') == 2
    printf ('Readme ..............................................................................Found [%d / %d]\n', 5, 5);
    total_points += 5;
  else
    printf ('Readme ..........................................................................Not Found [%d / %d]\n', 0, 5);
  endif
  
  printf ('Total = [%d / 100]\n', total_points);

  rmpath ('functions/');
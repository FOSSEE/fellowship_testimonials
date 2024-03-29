<?php
function fellowship_testimonials_edit() {
        $page_content = "";
        $fellowship_testimonials_edit_form = drupal_get_form("fellowship_testimonials_edit_form");
        $page_content .= drupal_render($fellowship_testimonials_edit_form);
        return $page_content;
    }
function fellowship_testimonials_edit_form($form, $form_state, $testimonial_id = 0) {
         $query = db_select('fellowship_testimonials');
         $query->fields('fellowship_testimonials');
         $query->condition('id', $testimonial_id);
         $result = $query->execute();
         $row = $result->fetchObject();
        $form = array();
        $form["activity"] = array(
            "#type" => 'select',
            "#title" => t('Select Activity'),
            "#options" => array(
                'Semester Long Internship' => 'Semester Long Internship',
                'FOSSEE Summer Fellowship' => 'FOSSEE Summer Fellowship'
                ),
            "#required" => TRUE,
            '#default_value' => $row->activity,
            //'#disabled' => TRUE,
        );
        $form["fellowship_year"] = array(
            "#type" => "textfield",
            "#title" => "Enter the year of participations",
            '#attributes' => array(
				'placeholder' => t('For eg: 2019')
			),
            "#default_value" => $row->year,
            "#required" => TRUE,
        );
        $form["fellowship_task"] = array(
            "#type" => "textfield",
            "#title" => "Enter floss catergory",
            '#attributes' => array(
				'placeholder' => t('For eg: Python, DWSIM, eSim etc')
			),
            "#default_value" => $row->fellowship_task,
            "#required" => TRUE,
        );
        $form["opt_text_or_video"] = array(
            "#type" => 'select',
            "#title" => t('Select type of experience'),
            "#options" => array(
                'T' => 'Text',
                'V' => 'Video'
                ),
            "#required" => TRUE,
            '#default_value' => $row->testimonial_type,
            '#disabled' => TRUE,
            /*'#ajax' => array(
                    'callback' => 'ajax_testimonial_type'
                )*/
        );
        if($row->testimonial_type == 'T'){
        $form["testimonial_text"] = array(
            "#type" => "text_format",
            '#format' => 'full_html',
            "#title" => "Enter the experience in text format",
            "#default_value" => $row->testimonial_text,
            '#prefix' => '<div id="testimonial-text">',
            '#suffix' => '</div>',
           // "#required" => TRUE,
            '#states' => array(
                'visible' => array(
                    ':input[name="opt_text_or_video"]' => array(
                        'value' => 'T'
                    )
                )
            ),
        );
        }
        else{
        $form["testimonial_video"] = array(
            "#type" => "textfield",
            "#title" => "URL to experience video",
            '#attributes' => array(
				'placeholder' => t('Copy paste the static url of the video, for eg: https://static.fossee.in/fossee/videos/FOSSEE_intern_Video/DSC_0006.m4v')
			),
            "#default_value" => $row->testimonial_video,
            '#size' => 255,
            '#maxlength' => 255,
            '#prefix' => '<div id="testimonial-video">',
            '#suffix' => '</div>',
            //"#required" => TRUE,
            '#states' => array(
                'visible' => array(
                    ':input[name="opt_text_or_video"]' => array(
                        'value' => 'V'
                    )
                )
            ),
        );
        }
        $query_s = db_select('fellows');
        $query_s->fields('fellows');
        $query_s->condition('t_id', $row->id);
        $result_s = $query_s->execute();
        $num_of_fellowresults = $result_s->rowCount();

  $form['fellows_fieldset'] = array(
            '#type' => 'fieldset',
            '#tree' => TRUE,
            '#prefix' => '<div id="fellows-fieldset-wrapper">',
            '#suffix' => '</div>'
        );

    if ($num_of_fellowresults != 0) {

            $form_state['num_fellows'] = $num_of_fellowresults;
            $temp = 0;
            $i = 0;
            while ($row_s = $result_s->fetchObject()) {
                $temp = $i;
                $form['fellows_fieldset'][$i]["s_text"] = array(
                    "#type" => "item",
                    "#markup" => "<h4><label>Pacticipant : " . ($temp + 1) . "</label></h4>"
                );
                $form['fellows_fieldset'][$i]["f_id"] = array(
                    "#type" => "hidden",
                    "#default_value" => $row_s->f_id
                );
                $form['fellows_fieldset'][$i]["fellowname"] = array(
                    "#type" => "textfield",
                    "#title" => "Name",
                    "#default_value" => $row_s->name
                );
                $form['fellows_fieldset'][$i]["institute"] = array(
                    "#type" => "textfield",
                    "#title" => "Institute",
                    "#default_value" => $row_s->institute
                );
                $form['fellows_fieldset'][$i]["place"] = array(
                    "#type" => "textfield",
                    "#title" => "Place",
                    "#default_value" => $row_s->place
                );
                $i++;
            }


            $form["fellows_count"] = array(
                "#type" => "hidden",
                "#value" => $temp
            );

        } 
        else {
            if (empty($form_state['num_fellows'])) {
                $form_state['num_fellows'] = 1;
            }
            $temp = 0;
            for ($i = 0; $i < $form_state['num_fellows']; $i++) {
                $temp = $i;
                $form['fellows_fieldset'][$i]["s_text"] = array(
                    "#type" => "item",
                    "#markup" => "<h4><label>fellows : " . ($temp + 1) . "</label></h4>"
                );
                $form['fellows_fieldset'][$i]["fellowname"] = array(
                    "#type" => "textfield",
                    "#title" => "Name",
                    "#default_value" => ""
                );
                $form['fellows_fieldset'][$i]["institute"] = array(
                    "#type" => "textfield",
                    "#title" => "University",
                    "#default_value" => ""
                );
                $form['fellows_fieldset'][$i]["place"] = array(
                    "#type" => "textfield",
                    "#title" => "Place",
                    "#default_value" => ""
                );
               
            }
            $form["fellows_count"] = array(
                "#type" => "hidden",
                "#value" => $temp
            );
            $form['fellows_fieldset']['add_fellows'] = array(
                '#type' => 'submit',
                '#value' => t('Add fellow'),
                '#limit_validation_errors' => array(),
                '#submit' => array(
                    'fellows_add_more_add_one'
                ),
                '#ajax' => array(
                    'callback' => 'fellows_add_more_callback',
                    'wrapper' => 'fellows-fieldset-wrapper'
                )
            );
            if ($form_state['num_fellows'] > 1) {
                $form['fellows_fieldset']['remove_fellows'] = array(
                    '#type' => 'submit',
                    '#value' => t('Remove'),
                    '#limit_validation_errors' => array(),
                    '#submit' => array(
                        'fellows_add_more_remove_one'
                    ),
                    '#ajax' => array(
                        'callback' => 'fellows_add_more_callback',
                        'wrapper' => 'fellows-fieldset-wrapper'
                    )
                );
            }
            if ($no_js_use) {
                if (!empty($form['fellows_fieldset']['remove_fellows']['#ajax'])) {
                    unset($form['fellows_fieldset']['remove_fellows']['#ajax']);
                }
                unset($form['fellows_fieldset']['add_fellows']['#ajax']);
            }
        }

        $form["testimonial_id"] = array(
            "#type" => "hidden",
            "#value" => $testimonial_id
        );
        $form["hidden"]= array(
            "#type" => "radios",
            "#options" => array(
            "1" => "Yes",
            "0" => "No",
            ),
            '#title' => t('Do you want to hide the testimonial from the public:'),
            '#default_value' => $row->hidden
        );
        $form["submit"] = array(
            "#type" => "submit",
            "#value" => "Submit"
        );
        return $form;
    }

/*function ajax_testimonial_type($form, $form_state){
    $type = $form_state['values']['opt_text_or_video'];
    if($type == 'V'){
        $commands[] = ajax_command_replace('#testimonial-video', drupal_render($form['testimonial_video']));
        $commands[] = ajax_command_html('#testimonial-text', '');
    }
    else{
        $commands[] = ajax_command_replace('#testimonial-text', drupal_render($form['testimonial_text']));
        $commands[] = ajax_command_html('#testimonial-video', '');
    }
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}*/

    function fellows_add_more_callback($form, $form_state) {
    return $form['fellows_fieldset'];
}


function fellows_add_more_add_one($form, &$form_state) {
    $form_state['num_fellows']++;
    $form_state['rebuild'] = TRUE;
    //$form_state['no_redirect'] = TRUE;
}


function fellows_add_more_remove_one($form, &$form_state) {
    if ($form_state['num_fellows'] > 1) {
        $form_state['num_fellows']--;
    }
    $form_state['rebuild'] = TRUE;
}

function fellowship_testimonials_edit_form_validate($form, &$form_state) {
        // for future use
    }

function fellowship_testimonials_edit_form_submit($form, &$form_state) {
        $v = $form_state['values'];
            if($v['opt_text_or_video'] == 'V'){
            $query = db_update('fellowship_testimonials');
            $query->fields(array(
                 'activity' => $v['activity'],
                 'year' => $v['fellowship_year'],
                 'fellowship_task' => $v['fellowship_task'],
                 'testimonial_video' => $v['testimonial_video'],
                 'hidden' => $v['hidden']['value']
            ));
        }

        else if($v['opt_text_or_video'] == 'T'){
            $query = db_update('fellowship_testimonials');
            $query->fields(array(
                'activity' => $v['activity'],
                'year' => $v['fellowship_year'],
                'fellowship_task' => $v['fellowship_task'],
                'testimonial_text' => $v['testimonial_text']['value'],
                'testimonial_text_format' => $v['testimonial_text']['format'],
                'hidden' => $v['hidden']['value']
            ));
        }
            $query->condition('id', $v['testimonial_id']);
            $result  = $query -> execute();
           
            $fellowsupload = 0;
            for ($i = 0; $i <= $v['fellows_count']; $i++) {
                $f_id=$v['fellows_fieldset'][$i]['f_id'];
            //var_dump($f_id);die;
            if ($f_id != "") {
                if ($v['fellows_fieldset'][$i]['fellowname'] != "") {
                    $query = db_update('fellows');
                   $query->fields(array(
                        'name' => $v['fellows_fieldset'][$i]['fellowname'],
                        'institute' => $v['fellows_fieldset'][$i]['institute'],
                        'place' => $v['fellows_fieldset'][$i]['place']
                    ));
                    $query->condition('f_id', $v['fellows_fieldset'][$i]['f_id']);
                    $fellowresult = $query -> execute();
                    if ($fellowresult != 0) {
                        $fellowsupload++;
                    }
                }
            }         
        }
        if((!$result) && (!$fellowresult)) {
            drupal_set_message("Something went wrong, please try again.", "error");
        } 
        else {
            drupal_set_message("Internship Experiences updated successfully", "status");
        }
        drupal_goto('internship-experiences/edit');
    }

function fellowship_testimonials_edit_all($testimonial_id=0) {
      
        $page_content = "";
        //var_dump($testimonial_id);die;
        if($testimonial_id){
              
              $fellowship_testimonials_edit_form = drupal_get_form("fellowship_testimonials_edit_form", $testimonial_id);
              $page_content .= drupal_render($fellowship_testimonials_edit_form);
        } else {
            $query = db_select('fellowship_testimonials');
            $query->fields('fellowship_testimonials');
            $query->orderBy('id', DESC);
            //$query->condition('id', $speakerrow->t_id);
            $result = $query->execute();

                        $headers = array(
                "Name", "Institute", "Activity Name", "Type", "Action", "Status"
            );

            $rows = array();
            while($row = $result->fetchObject()) 
            {
              $speakerquery = db_query("SELECT GROUP_CONCAT(name separator ', ') as name, GROUP_CONCAT(institute separator ', ') as institute FROM fellows WHERE t_id = :t_id GROUP BY t_id", array(
                    ":t_id" => $row->id
                ));
              if($row->testimonial_type == 'T'){
                $testimonial_type = "Text";
              }
              else{
                $testimonial_type = "Video";
              }
              if($row->hidden == 1){
                $display_status = "Hidden to public";
              }
              else{
                $display_status = "Displayed to public";
              }
                /*$speakerquery = db_select('fellows');
            $speakerquery->fields('fellows');
            $speakerquery->condition('t_id', $row->id);
            $speakerresult = $speakerquery->execute();*/
            while($speakerrow = $speakerquery->fetchObject()){
                $fellow_name = $speakerrow->name;
                $institute = $speakerrow->institute;
            }
            //$speakerrow = $speakerresult->fetchObject();
                $item = array(
                    $fellow_name,
                    $institute,
                    $row -> activity,
                    $testimonial_type,
                    l("Edit", "internship-experiences/edit/{$row->id}"),
                   // l("Delete", "fellowship-testimonials/delete/{$row->id}")
                    $display_status

                );
                array_push($rows, $item);
            //}
        }
            //$page_content .= theme("table", $headers, $rows);
            $page_content .= theme('table', array('header' => $headers, 'rows' => $rows ));
        }
        return $page_content;
    }

<?php
function fellowship_testimonials_add_all() {
        $page_content = "";
        $fellowship_testimonials_add_form = drupal_get_form("fellowship_testimonials_add_form");
        $page_content .= drupal_render($fellowship_testimonials_add_form);
        return $page_content;
    }
function fellowship_testimonials_add_form($form,$form_state, $no_js_use = FALSE, $testimonial_id = 0) {
         $testimonial_id = arg(2);
         //var_dump($testimonial_id);die;
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
                'Semster-long internship' => 'Semster-long internship',
                'Fossee Summer fellowship' => 'Fossee Summer fellowship'
                ),
            "#required" => TRUE,
        );
        $form["fellowship_year"] = array(
            "#type" => "textfield",
            "#title" => "Enter the year of participations",
            '#attributes' => array(
				'placeholder' => t('For eg: 2019')
			),
            "#required" => TRUE
        );
        $form["fellowship_task"] = array(
            "#type" => "textfield",
            "#title" => "Enter floss catergory",
            '#attributes' => array(
				'placeholder' => t('For eg: Python, DWSIM, eSim etc')
			),
            "#required" => TRUE
        );
        $form["opt_text_or_video"] = array(
            "#type" => 'select',
            "#title" => t('Select type of experience'),
            "#options" => array(
                'T' => 'Text',
                'V' => 'Video'
                ),
            "#required" => TRUE,
            '#ajax' => array(
                    'callback' => 'ajax_testimonial_type'
                )
        );
        /*$form["testimonial_text"] = array(
            "#type" => 'textfield',
            //'#format' => 'full_html',
            "#title" => t('Enter the testimonial by user'),
            "#required" => TRUE,
            '#states' => array(
                'visible' => array(
                    ':input[name="opt_text_or_video"]' => array(
                        'value' => 'T'
                    )
                )
            ),
            '#default_value' => $row->testimonial_text
        );*/
        $form["testimonial_text"] = array(
            "#type" => "text_format",
            '#format' => 'full_html',
            "#title" => "Experience in text format",
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
        $form["testimonial_video"] = array(
            "#type" => "textfield",
            "#title" => "URL to experience video",
            '#attributes' => array(
				'placeholder' => t('Copy paste the static url of the video, for eg: https://static.fossee.in/fossee/videos/FOSSEE_intern_Video/DSC_0006.m4v')
			),
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

  $form['fellows_fieldset'] = array(
            '#type' => 'fieldset',
            '#tree' => TRUE,
            '#prefix' => '<div id="fellows-fieldset-wrapper">',
            '#suffix' => '</div>'
        ); 
            if (empty($form_state['num_fellows'])) {
                $form_state['num_fellows'] = 1;
            }
            $temp = 0;
            for ($i = 0; $i < $form_state['num_fellows']; $i++) {
                $temp = $i;
                $form['fellows_fieldset'][$i]["s_text"] = array(
                    "#type" => "item",
                    "#markup" => "<h4><label>Pacticipant : " . ($temp + 1) . "</label></h4>"
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
                '#value' => t('Add Pacticipant'),
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
        $form["submit"] = array(
            "#type" => "submit",
            "#value" => "Submit"
        );
        return $form;
    }

function ajax_testimonial_type($form, $form_state){
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
}

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

    function fellowship_testimonials_add_form_validate($form, &$form_state) {
        // for future use
    }

    function fellowship_testimonials_add_form_submit($form, &$form_state) {
        $v = $form_state["values"];
       
            if($v['opt_text_or_video'] == 'V'){
            $query = "
                INSERT INTO fellowship_testimonials(activity, year, fellowship_task, testimonial_video, testimonial_type)
                VALUES (:activity, :year, :fellowship_task, :testimonial_video, :testimonial_type)";
            $args = array(
                ':activity' => $v["activity"], 
                ':year' => $v["fellowship_year"],
                ':fellowship_task' => $v["fellowship_task"],
                ':testimonial_video' => $v["testimonial_video"],
                ':testimonial_type' => 'V'
                );
            }
            else if($v['opt_text_or_video'] == 'T'){
                $query = "
                INSERT INTO fellowship_testimonials(activity, year, fellowship_task, testimonial_text, testimonial_text_format, testimonial_type)
                VALUES (:activity, :year, :fellowship_task, :testimonial_text, :testimonial_text_format, :testimonial_type)";
            $args = array(
                ':activity' => $v["activity"], 
                ':year' => $v["fellowship_year"],
                ':fellowship_task' => $v["fellowship_task"],
                ':testimonial_text' => $v["testimonial_text"]["value"],
                ':testimonial_text_format' => $v["testimonial_text"]["format"],
                ':testimonial_type' => 'T'
                );
            }
            $result = db_query($query,$args, array(
        'return' => Database::RETURN_INSERT_ID
    ));
            $fellowsupload = 0;
            for ($i = 0; $i <= $v["fellows_count"]; $i++) {
                //$f_id=$v['fellows_fieldset'][$i]["f_id"];
                if ($v['fellows_fieldset'][$i]["fellowname"] != "") {
                    $fellowsquery = "INSERT INTO fellows (t_id,name,institute,place) VALUES (:t_id,:name,:institute,:place)";
                    $fellowsargs = array(
                        ":t_id" => $result,
                        ":name" => trim($v['fellows_fieldset'][$i]["fellowname"]),
                        ":institute" => trim($v['fellows_fieldset'][$i]["institute"]),
                        ":place" => trim($v['fellows_fieldset'][$i]["place"])
                    );
                    /* storing the row id in $result */
                    $fellowsresult = db_query($fellowsquery, $fellowsargs, array(
                        'return' => Database::RETURN_INSERT_ID
                    ));
                    if ($fellowsresult != 0) {
                        $fellowsupload++;
                    }
                }
            }
        //var_dump($result->name);die;
        if(!$result) {
            drupal_set_message("Something went wrong, please try again.", "error");
        } else {
            drupal_set_message("Internship Experiences added successfully", "status");
        }
        drupal_goto('internship-experiences/edit');
    }
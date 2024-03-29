<?php
function animation_hackathon_vle_registration() {
        $page_content = "";
        $animation_hackathon_vle_registration_form = drupal_get_form("animation_hackathon_vle_registration_form");
        $page_content .= drupal_render($animation_hackathon_vle_registration_form);
        return $page_content;
    }

function animation_hackathon_vle_registration_form($form, &$form_state) {
        $form = array();
        $state =  _hackathon_list_of_states();
	$selected_state = isset($form_state['values']['all_state'])?$form_state['values']['all_state']:key($state);
	$district = _hackathon_list_of_district();
	$selected_district = isset($form_state['values']['district'])?$form_state['values']['district']:key($district);
	$city = _hackathon_list_of_cities();
	$selected_city = isset($form_state['values']['city'])?$form_state['values']['city']:key($city);
        $form["registration_instructions"] = array(
        	"#type" => 'item',
        	'#markup' => '<p>This is the registration form to participate in this Hackathon.</p>
<p>The form should be filled ONLY by the team lead. In case you are participating as an individual, you become the team lead. Please fill in the details accurately and register for the All India 2D Animation Hackathon.</p>
<p>Please note that:</p>
<ol>
<li>You have to use Synfig Studio to create 2D Animation. You may use Inkscape, GIMP, or any other open-source software to create the supporting graphics.</li>
<li>Your animation must be developed entirely during the All India 2D animation Hackathon.</li>
</ol>
<p>The contact information mentioned in this form will be used for all communication purposes, to print on the certificates, etc. Hence, kindly fill the form carefully.</p>'
        );
        $form['country'] = array(
		'#type' => 'select',
		'#title' => t('Country'),
		'#options' => array(
			'India' => 'India',
			//'Others' => 'Others'
		),
		'#default_value' => 'India',
		'#prefix' => '<div id="ajax-country-list-replace">',
		'#suffix' => '</div>',
		'#ajax' => array(
			'callback' => 'ajax_get_city_list_callback',
			),
		'#required' => TRUE,
		'#tree' => TRUE,
		'#validated' => TRUE
	);
        $form['all_state'] = array(
		'#type' => 'select',
		'#title' => t('State/UT'),
		'#options' => _hackathon_list_of_states(),
		//'#empty_value' => '0',
		//'#empty_option' => '- Select -',
		'#default_value' => '0',
		'#prefix' => '<div id="ajax-state-list-replace">',
		'#suffix' => '</div>',
		'#required' => TRUE,
		'#ajax' => array(
			'callback' => 'ajax_get_district_list_callback',
			),
		'#validated' => TRUE,
		'#states' => array(
			'visible' => array(
				':input[name="country"]' => array(
					'value' => 'India'
				)
			)
		)
	);
	$form['district'] = array(
		'#type' => 'select',
		'#title' => t('District/Area'),
		'#options' => _hackathon_list_of_district($selected_state),
		'#empty_value' => '0',
		'#empty_option' => '- Select -',
		'#prefix' => '<div id="ajax-district-list-replace">',
		'#suffix' => '</div>',
		'#validated' => TRUE,
		'#required' => TRUE,
		'#ajax' => array(
			'callback' => 'ajax_get_city_list_callback',
			),
		'#states' => array(
			'invisible' => array(
				':input[name="all_state"]' => array(
					'value' => '0'
				)
			)
		)
	);
	$form['city'] = array(
		'#type' => 'select',
		'#title' => t('Block'),
		'#options' => _hackathon_list_of_cities($selected_state, $selected_district),
		'#default_value' => '0',
		'#empty_value' => '0',
		'#empty_option' => '- Select -',
		'#prefix' => '<div id="ajax-city-list-replace">',
		'#suffix' => '</div>',
		'#validated' => TRUE,
		'#required' => TRUE,
		'#states' => array(
			'invisible' => array(
				':input[name="district"]' => array(
					'value' => '0'
				)
			)
		)
	);
	$form['csc_id'] = array(
            "#type" => 'textfield',
            "#title" => t('CSC ID'),
            "#required" => TRUE,
            '#maxlength' => 12
        );

        $form['team_member_1'] = array(
            '#type' => 'fieldset',
            '#tree' => TRUE,
        ); 
        $form["team_member_1"]["name"] = array(
            "#type" => 'textfield',
            "#title" => t('Name of team member 1 (team lead)'),
            "#description" => t('This team member will be considered as the Team Lead who shall be our point of contact.'),
            "#required" => TRUE,
        );
        $form["team_member_1"]["email"] = array(
            "#type" => "textfield",
            "#title" => "Email Id of team member 1",
            "#required" => TRUE
        );
        $form["team_member_1"]["contact"] = array(
            "#type" => "textfield",
            "#title" => "Contact number of team member 1",
            "#description" => t("Please provide an active phone number"),
            "#required" => TRUE,
            '#maxlength' => 10
        );
        $form["team_member_1"]["gender"] = array(
            "#type" => 'select',
            "#title" => t('Gender of team member 1'),
            "#options" => array(
                'Male' => 'Male',
                'Female' => 'Female',
                'Prefer not to say' => 'Prefer not to say'
                ),
            "#required" => TRUE,
        );
        $form["team_member_1"]["category"] = array(
            "#type" => 'select',
            "#title" => t('Category of team member 1'),
            "#options" => array(
                'School student' => 'School student',
                'College student' => 'College student',
                'Working Professional' => 'Working Professional',
                'Others' => 'Others'
                ),
            "#required" => TRUE,
        );
        $form["team_member_1"]["institution"] = array(
            "#type" => "textfield",
            "#title" => "School/ College/ Institution / Organisation name of team member 1",
            "#required" => TRUE
        );
        $form['team_size'] =array(
        	"#type" => 'select',
            "#title" => t('Do you have a second person in your team?'),
            "#options" => array(
                'Yes' => 'Yes',
                'No' => 'No',
                ),
            "#required" => TRUE,
        );
                $form['team_member_2'] = array(
            '#type' => 'fieldset',
            '#tree' => TRUE,
            '#states' => array(
            'visible' => array(
                ':input[name="team_size"]' => array(
                    'value' => 'Yes'
                )
            )
        )
        ); 
        $form["team_member_2"]["name"] = array(
            "#type" => 'textfield',
            "#title" => t('Name of team member 2'),
            "#required" => TRUE,
            '#validated' => TRUE
        );
        $form["team_member_2"]["email"] = array(
            "#type" => "textfield",
            "#title" => "Email Id of team member 2",
            "#required" => TRUE,
            '#validated' => TRUE
        );
        $form["team_member_2"]["contact"] = array(
            "#type" => "textfield",
            "#title" => "Contact number of team member 2",
            "#description" => t("Please provide an active phone number"),
            "#required" => TRUE,
            '#maxlength' => 10,
            '#validated' => TRUE
        );
        $form["team_member_2"]["gender"] = array(
            "#type" => 'select',
            "#title" => t('Gender of team member 2'),
            "#options" => array(
                'Male' => 'Male',
                'Female' => 'Female',
                'Prefer not to say' => 'Prefer not to say'
                ),
            "#required" => TRUE,
            '#validated' => TRUE
        );
        $form["team_member_2"]["category"] = array(
            "#type" => 'select',
            "#title" => t('Category of team member 2'),
            "#options" => array(
                'School student' => 'School student',
                'College student' => 'College student',
                'Working Professional' => 'Working Professional',
                'Others' => 'Others'
                ),
            "#required" => TRUE,
            '#validated' => TRUE
        );
        $form["team_member_2"]["institution"] = array(
            "#type" => "textfield",
            "#title" => "School/ College/ Institution / Organisation name of team member 2",
            "#required" => TRUE,
            '#validated' => TRUE
        );
        $form["synfig_knowledge"] = array(
	        '#type' => 'radios',
			'#title' => t('Do you or does your team member know Synfig Studio?'),
			'#options' => array(
				'Yes' => 'Yes',
				'No' => 'No'
			),
			'#required' => TRUE
        );
	$form['other_softwares_used'] = array(
		'#type' => 'checkboxes',
		'#title' => t('Which other software you are planning to use in this Hackathon? (You should use open source software only)'),
		'#options' => array(
		'Inkscape' => t('Inkscape  (It is free and opensource software to create vector drawing)'),
		'Krita' => t('Krita (It is free and opensource software for drawing)'),
		'GIMP' => t('GIMP (It is free and opensource software to image manupulation)'),
		'Openshot' => t('Openshot (It is free and opensource software for video compositing)'),
		'Audacity' => t('Audacity (It is free and opensource software for sound editing)'),
		'LMMS' => t('LMMS (It is free and opensource software for creating music notes)'),
		'Other' => t('Other')),
		'#required' => TRUE
	);
	$form['other_software_apart_from_list'] = array(
		'#type' => 'textarea',
		'#size' => 300,
		'#maxlength' => 300,
		'#states' => array(
			'visible' => array(
				':input[name="other_softwares_used[Other]"]' => array(
					'checked' => TRUE
				)
			)
		)
		//'#required' => FALSE,
	);
	$form['information_about_event'] = array(
		'#type' => 'checkboxes',
		'#title' => t('How did you come to know about this Hackathon?'),
		'#options' => array(
		'Through social media' => t('Through social media'),
		'Through a friend' => t('Through a friend'),
		'Through school/college teacher/administration' => t('Through school/college teacher/administration'),
		'Through Common Service Centre (CSC)' => 'Through Common Service Centre (CSC)'
	),
		'#required' => TRUE
	);
	$form['about_team'] = array(
		'#type' => 'textarea',
		'#title' => t('Please tell us a little more about your team.  If you are student(s), which school/college, which class/year, etc.  If you are working professional(s), what kind of work you do, etc.'),
	);
	$form['term_condition'] = array(
		'#type' => 'radios',
		'#title' => t('I have read all the instructions given on the weblink: <a href="https://hackathon.fossee.in/2D-animation" target="_blank">https://hackathon.fossee.in/2D-animation</a>'),
		'#options' => array(
			'Yes' => 'Yes',
			'No' => 'No'
		),
		'#required' => TRUE
	);
        $form["submit"] = array(
            "#type" => "submit",
            "#value" => "Submit"
        );
        return $form;
    }


   function ajax_get_city_list_callback($form, $form_state)
{
    $state_default_value = $form_state['values']['all_state'];
    $district_default_value = $form_state['values']['district'];
    if ($district_default_value != '0')
    {
        $form['city']['#options'] = _hackathon_list_of_cities($state_default_value, $district_default_value);
        $commands[] = ajax_command_replace("#ajax-city-list-replace", drupal_render($form['city']));
        
    }else{
        $form['city']['#options'] = array('0' => '- Select -');
        $commands[] = ajax_command_replace("#ajax-city-list-replace", drupal_render($form['city']));
    }
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}
function ajax_get_district_list_callback($form, $form_state)
{
    $state_default_value = $form_state['values']['all_state'];
    if ($state_default_value != '0')
    {
        $form['district']['#options'] = _hackathon_list_of_district($state_default_value);
        $commands[] = ajax_command_replace("#ajax-district-list-replace", drupal_render($form['district']));
        $form['city']['#options'] = array('0' => '- Select -');
        $commands[] = ajax_command_replace("#ajax-city-list-replace", drupal_render($form['city']));
    }else{
        $form['district']['#options'] = array('0' => '- Select -');
        $commands[] = ajax_command_replace("#ajax-district-list-replace", drupal_render($form['district']));
        $form['city']['#options'] = array('0' => '- Select -');
        $commands[] = ajax_command_replace("#ajax-city-list-replace", drupal_render($form['city']));
    }
    return array(
        '#type' => 'ajax',
        '#commands' => $commands
    );
}


function animation_hackathon_vle_registration_form_validate($form, &$form_state) {
	$v = $form_state['values']['team_member_2'];
	$team_lead_email = $form_state['values']['team_member_1']['email'];
	$query = db_select('animation_hackathon_vle_registration');
         $query->fields('animation_hackathon_vle_registration');
         $query->condition('team_member_1_email', $team_lead_email);
         $result = $query->execute();
         $row = $result->fetchObject();
         if($row){
         	drupal_set_message('You have already registered', 'error');
         	drupal_goto('animation-hackathon/vle-registration');
         }
         /*if (!valid_email_address($form_state['values']['team_member_1']['mail'])) {
  form_set_error('submitted][email_address', t('The email address appears to be invalid.'));
}*/
	if($form_state['values']['team_size'] == 'Yes'){
		if($v['name'] == '')
			form_set_error('team_member_2][name', 'Enter name of team member 2');
		if($v['email'] == '')
			form_set_error('team_member_2][email', 'Enter email id of team member 2');
		if($v['contact'] == '')
			form_set_error('team_member_2][contact', 'Enter contact of team member 2');
		if($v['gender'] == '')
			form_set_error('team_member_2][gender', 'Enter gender id of team member 2');
		if($v['category'] == '')
			form_set_error('team_member_2][category', 'Enter category of team member 2');
		if($v['institution'] == '')
			form_set_error('team_member_2][institution', 'Enter institution id of team member 2');
		/*else if (!valid_email_address($v['email'])) {
			form_set_error('team_member_2][email', 'The email address appears to be invalid.');
		}*/

	}
}

function animation_hackathon_vle_registration_form_submit($form, &$form_state){
	$v = $form_state['values'];
	if (isset($_POST['other_softwares_used']))
	{
		if (!($form_state['values']['other_software_apart_from_list']))
		{
			$other_softwares_used = implode(", ", $_POST['other_softwares_used']);
		} //!($form_state['values']['other_reason'])
		else
		{
			$other_softwares_used = implode(", ", $_POST['other_softwares_used']);
			$other_softwares_used = $other_softwares_used . "-" . " " . $form_state['values']['other_software_apart_from_list'];
		}
	} //isset($_POST['other_softwares_used'])
	if (isset($_POST['information_about_event']))
	{
			$source_of_information = implode(", ", $_POST['information_about_event']);
	} //isset($_POST['other_softwares_used'])

	if($v['team_size'] == 'Yes'){
		$query = "INSERT INTO animation_hackathon_vle_registration 
		(country, state, district, block_name, csc_id, team_size, team_member_1_name, team_member_1_email, team_member_1_contact, team_member_1_gender, team_member_1_category, team_member_1_institution, team_member_2_name, team_member_2_email, team_member_2_contact, team_member_2_gender, team_member_2_category, team_member_2_institution, know_synfig, other_softwares_used, information_about_event, about_team, terms_and_condition, registration_timestamp) VALUES (:country, :state, :district, :block_name, :csc_id, :team_size, :team_member_1_name, :team_member_1_email, :team_member_1_contact, :team_member_1_gender, :team_member_1_category, :team_member_1_institution, :team_member_2_name, :team_member_2_email, :team_member_2_contact, :team_member_2_gender, :team_member_2_category, :team_member_2_institution, :know_synfig, :other_softwares_used, :information_about_event, :about_team, :terms_and_condition, :registration_timestamp)";
		$args = array(
			":country" => $v['country'],
			":state" => $v['all_state'],
			":district" => $v['district'],
			":block_name" => $v['city'],
			":csc_id" => $v['csc_id'],
			":team_size" => 2,
			":team_member_1_name" => $v['team_member_1']['name'],
			":team_member_1_email" => $v['team_member_1']['email'],
			":team_member_1_contact" => $v['team_member_1']['contact'],
			":team_member_1_gender" => $v['team_member_1']['gender'],
			":team_member_1_category" => $v['team_member_1']['category'],
			":team_member_1_institution" => $v['team_member_1']['institution'],
			":team_member_2_name" => $v['team_member_2']['name'],
			":team_member_2_email" => $v['team_member_2']['email'],
			":team_member_2_contact" => $v['team_member_2']['contact'],
			":team_member_2_gender" => $v['team_member_2']['gender'],
			":team_member_2_category" => $v['team_member_2']['category'],
			":team_member_2_institution" => $v['team_member_2']['institution'],
			":know_synfig" => $v['synfig_knowledge'],
			":other_softwares_used" => $other_softwares_used,
			":information_about_event" => $source_of_information,
			":about_team" => $v['about_team'],
			":terms_and_condition" => $v['term_condition'],
			":registration_timestamp" => time()
		);
		$result = db_query($query, $args);
		if(!$result){
			drupal_set_message('Registration not successful, please try again', 'error');
		}
		else{
			drupal_set_message('Registration successful', 'status');
		}
	}
	else{
		$query = "INSERT INTO animation_hackathon_vle_registration 
		(country, state, district, block_name, csc_id, team_size, team_member_1_name, team_member_1_email, team_member_1_contact, team_member_1_gender, team_member_1_category, team_member_1_institution, team_member_2_name, team_member_2_email, team_member_2_contact, team_member_2_gender, team_member_2_category, team_member_2_institution, know_synfig, other_softwares_used, information_about_event, about_team, terms_and_condition, registration_timestamp) VALUES (:country, :state, :district, :block_name, :csc_id, :team_size, :team_member_1_name, :team_member_1_email, :team_member_1_contact, :team_member_1_gender, :team_member_1_category, :team_member_1_institution, :team_member_2_name, :team_member_2_email, :team_member_2_contact, :team_member_2_gender, :team_member_2_category, :team_member_2_institution, :know_synfig, :other_softwares_used, :information_about_event, :about_team, :terms_and_condition, :registration_timestamp)";
		$args = array(
			":country" => $v['country'],
			":state" => $v['all_state'],
			":district" => $v['district'],
			":block_name" => $v['city'],
			":csc_id" => $v['csc_id'],
			":team_size" => 1,
			":team_member_1_name" => $v['team_member_1']['name'],
			":team_member_1_email" => $v['team_member_1']['email'],
			":team_member_1_contact" => $v['team_member_1']['contact'],
			":team_member_1_gender" => $v['team_member_1']['gender'],
			":team_member_1_category" => $v['team_member_1']['category'],
			":team_member_1_institution" => $v['team_member_1']['institution'],
			":team_member_2_name" => 'NA',
			":team_member_2_email" => 'NA',
			":team_member_2_contact" => 'NA',
			":team_member_2_gender" => 'NA',
			":team_member_2_category" => 'NA',
			":team_member_2_institution" => 'NA',
			":know_synfig" => $v['synfig_knowledge'],
			":other_softwares_used" => $other_softwares_used,
			":information_about_event" => $source_of_information,
			":about_team" => $v['about_team'],
			":terms_and_condition" => $v['term_condition'],
			":registration_timestamp" => time()
		);
		$result = db_query($query, $args);
		if(!$result){
			drupal_set_message('Registration not successful, please try again', 'error');
		}
		else{
			drupal_set_message('Registration successful', 'status');
		}
	}
}


function view_animation_hackathon_vle_registrations() {
        $page_content = "";
        
         $query = db_select('animation_hackathon_vle_registration');
         $query->fields('animation_hackathon_vle_registration');
        $result = $query->execute();
       $page_content .= "Total number of registrations: " . $result->rowCount() . "<br>Click <a href='registrations/download'>here</a> to download the CSV with participant details";
        return $page_content;
    }


    function download_registration_details(){
    global $user;
    /* get pending submissions to be approved */
    
    $root_path = vle_registration_csv_path();
    $my_submission_rows = array();
    $query = db_select('animation_hackathon_vle_registration');
    $query->fields('animation_hackathon_vle_registration');
    $all_submissions_q = $query->execute();
    $participants_email_id_file = $root_path . "participants.csv";
    $fp = fopen($participants_email_id_file, "w");
            /* making the first row */
            $item = array(
            	"Country",
            	"State",
            	"District",
            	"Block",
            	"CSC ID",
            	"Team size",
            	"Team member 1 Name",
            	"Team member 1 Email",
            	"Team member 1 Contact",
            	"Team member 1 Gender",
            	"Team member 1 Category",
            	"Team member 1 Institution",
            	"Team member 2 Name",
            	"Team member 2 Email",
            	"Team member 2 Contact",
            	"Team member 2 Gender",
            	"Team member 2 Category",
            	"Team member 2 Institution",
                "Know Synfig",
                "Other Softwares used",
                "How did you come to know about the event?",
                "About team",
                "Date of registration"
            );
            fputcsv($fp, $item);

            while($row = $all_submissions_q->fetchObject()) {
                $item = array(
                    $row->country,
                    $row->state,
                    $row->district,
                    $row->block_name,
                    $row->csc_id,
                    $row->team_size,
                    $row->team_member_1_name,
                    $row->team_member_1_email,
                    $row->team_member_1_contact,
                    $row->team_member_1_gender,
                    $row->team_member_1_category,
                    $row->team_member_1_institution,
                    $row->team_member_2_name,
                    $row->team_member_2_email,
                    $row->team_member_2_contact,
                    $row->team_member_2_gender,
                    $row->team_member_2_category,
                    $row->team_member_2_institution,
                    $row->know_synfig,
                    $row->other_softwares_used,
                    $row->information_about_event,
                    $row->about_team,
                    date("d-m-Y", $row->registration_timestamp)
                );
                fputcsv($fp, $item);
            }
            fclose($fp);
            if($participants_email_id_file){
        ob_clean();
            header("Pragma: public");
            header("Expires: 0");
            header("Cache-Control: must-revalidate, post-check=0, pre-check=0");
            header("Cache-Control: public");
            header("Content-Description: File Transfer");
            header('Content-Type: application/csv');
            header('Content-disposition: attachment; filename=participant-details.csv');
            header('Content-Length:' . filesize($participants_email_id_file));
            header("Content-Transfer-Encoding: binary");
            header('Expires: 0');
            header('Pragma: no-cache');
            readfile($participants_email_id_file);
            /*ob_end_flush();
            ob_clean();
            flush();*/
        }
}
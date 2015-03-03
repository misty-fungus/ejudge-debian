// This is an auto-generated file, do not edit
// Generated 2012/07/03 08:15:01

#ifndef __PROBLEM_CONFIG_META_H__
#define __PROBLEM_CONFIG_META_H__

#include <stdlib.h>

enum
{
  META_PROBLEM_CONFIG_SECTION_manual_checking = 1,
  META_PROBLEM_CONFIG_SECTION_check_presentation,
  META_PROBLEM_CONFIG_SECTION_scoring_checker,
  META_PROBLEM_CONFIG_SECTION_use_stdin,
  META_PROBLEM_CONFIG_SECTION_use_stdout,
  META_PROBLEM_CONFIG_SECTION_combined_stdin,
  META_PROBLEM_CONFIG_SECTION_combined_stdout,
  META_PROBLEM_CONFIG_SECTION_binary_input,
  META_PROBLEM_CONFIG_SECTION_binary,
  META_PROBLEM_CONFIG_SECTION_ignore_exit_code,
  META_PROBLEM_CONFIG_SECTION_olympiad_mode,
  META_PROBLEM_CONFIG_SECTION_score_latest,
  META_PROBLEM_CONFIG_SECTION_score_latest_or_unmarked,
  META_PROBLEM_CONFIG_SECTION_use_ac_not_ok,
  META_PROBLEM_CONFIG_SECTION_ignore_prev_ac,
  META_PROBLEM_CONFIG_SECTION_team_enable_rep_view,
  META_PROBLEM_CONFIG_SECTION_team_enable_ce_view,
  META_PROBLEM_CONFIG_SECTION_team_show_judge_report,
  META_PROBLEM_CONFIG_SECTION_ignore_compile_errors,
  META_PROBLEM_CONFIG_SECTION_variable_full_score,
  META_PROBLEM_CONFIG_SECTION_ignore_penalty,
  META_PROBLEM_CONFIG_SECTION_use_corr,
  META_PROBLEM_CONFIG_SECTION_use_info,
  META_PROBLEM_CONFIG_SECTION_use_tgz,
  META_PROBLEM_CONFIG_SECTION_accept_partial,
  META_PROBLEM_CONFIG_SECTION_disable_user_submit,
  META_PROBLEM_CONFIG_SECTION_disable_tab,
  META_PROBLEM_CONFIG_SECTION_restricted_statement,
  META_PROBLEM_CONFIG_SECTION_disable_submit_after_ok,
  META_PROBLEM_CONFIG_SECTION_disable_auto_testing,
  META_PROBLEM_CONFIG_SECTION_disable_testing,
  META_PROBLEM_CONFIG_SECTION_enable_compilation,
  META_PROBLEM_CONFIG_SECTION_skip_testing,
  META_PROBLEM_CONFIG_SECTION_hidden,
  META_PROBLEM_CONFIG_SECTION_stand_hide_time,
  META_PROBLEM_CONFIG_SECTION_advance_to_next,
  META_PROBLEM_CONFIG_SECTION_disable_ctrl_chars,
  META_PROBLEM_CONFIG_SECTION_enable_text_form,
  META_PROBLEM_CONFIG_SECTION_stand_ignore_score,
  META_PROBLEM_CONFIG_SECTION_stand_last_column,
  META_PROBLEM_CONFIG_SECTION_disable_security,
  META_PROBLEM_CONFIG_SECTION_valuer_sets_marked,
  META_PROBLEM_CONFIG_SECTION_ignore_unmarked,
  META_PROBLEM_CONFIG_SECTION_disable_stderr,
  META_PROBLEM_CONFIG_SECTION_id,
  META_PROBLEM_CONFIG_SECTION_real_time_limit,
  META_PROBLEM_CONFIG_SECTION_time_limit,
  META_PROBLEM_CONFIG_SECTION_time_limit_millis,
  META_PROBLEM_CONFIG_SECTION_full_score,
  META_PROBLEM_CONFIG_SECTION_full_user_score,
  META_PROBLEM_CONFIG_SECTION_test_score,
  META_PROBLEM_CONFIG_SECTION_run_penalty,
  META_PROBLEM_CONFIG_SECTION_acm_run_penalty,
  META_PROBLEM_CONFIG_SECTION_disqualified_penalty,
  META_PROBLEM_CONFIG_SECTION_min_tests_to_accept,
  META_PROBLEM_CONFIG_SECTION_checker_real_time_limit,
  META_PROBLEM_CONFIG_SECTION_priority_adjustment,
  META_PROBLEM_CONFIG_SECTION_score_multiplier,
  META_PROBLEM_CONFIG_SECTION_prev_runs_to_show,
  META_PROBLEM_CONFIG_SECTION_interactor_time_limit,
  META_PROBLEM_CONFIG_SECTION_max_open_file_count,
  META_PROBLEM_CONFIG_SECTION_max_process_count,
  META_PROBLEM_CONFIG_SECTION_tests_to_accept,
  META_PROBLEM_CONFIG_SECTION_deadline,
  META_PROBLEM_CONFIG_SECTION_start_date,
  META_PROBLEM_CONFIG_SECTION_max_vm_size,
  META_PROBLEM_CONFIG_SECTION_max_data_size,
  META_PROBLEM_CONFIG_SECTION_max_stack_size,
  META_PROBLEM_CONFIG_SECTION_max_core_size,
  META_PROBLEM_CONFIG_SECTION_max_file_size,
  META_PROBLEM_CONFIG_SECTION_type,
  META_PROBLEM_CONFIG_SECTION_short_name,
  META_PROBLEM_CONFIG_SECTION_long_name,
  META_PROBLEM_CONFIG_SECTION_long_name_en,
  META_PROBLEM_CONFIG_SECTION_stand_name,
  META_PROBLEM_CONFIG_SECTION_internal_name,
  META_PROBLEM_CONFIG_SECTION_test_dir,
  META_PROBLEM_CONFIG_SECTION_test_sfx,
  META_PROBLEM_CONFIG_SECTION_corr_sfx,
  META_PROBLEM_CONFIG_SECTION_info_sfx,
  META_PROBLEM_CONFIG_SECTION_tgz_sfx,
  META_PROBLEM_CONFIG_SECTION_tgzdir_sfx,
  META_PROBLEM_CONFIG_SECTION_input_file,
  META_PROBLEM_CONFIG_SECTION_output_file,
  META_PROBLEM_CONFIG_SECTION_test_score_list,
  META_PROBLEM_CONFIG_SECTION_score_tests,
  META_PROBLEM_CONFIG_SECTION_standard_checker,
  META_PROBLEM_CONFIG_SECTION_spelling,
  META_PROBLEM_CONFIG_SECTION_plugin_file,
  META_PROBLEM_CONFIG_SECTION_xml_file,
  META_PROBLEM_CONFIG_SECTION_stand_attr,
  META_PROBLEM_CONFIG_SECTION_source_header,
  META_PROBLEM_CONFIG_SECTION_source_footer,
  META_PROBLEM_CONFIG_SECTION_test_pat,
  META_PROBLEM_CONFIG_SECTION_corr_pat,
  META_PROBLEM_CONFIG_SECTION_info_pat,
  META_PROBLEM_CONFIG_SECTION_tgz_pat,
  META_PROBLEM_CONFIG_SECTION_tgzdir_pat,
  META_PROBLEM_CONFIG_SECTION_normalization,
  META_PROBLEM_CONFIG_SECTION_check_cmd,
  META_PROBLEM_CONFIG_SECTION_valuer_cmd,
  META_PROBLEM_CONFIG_SECTION_interactor_cmd,
  META_PROBLEM_CONFIG_SECTION_style_checker_cmd,
  META_PROBLEM_CONFIG_SECTION_test_checker_cmd,
  META_PROBLEM_CONFIG_SECTION_init_cmd,
  META_PROBLEM_CONFIG_SECTION_solution_src,
  META_PROBLEM_CONFIG_SECTION_solution_cmd,
  META_PROBLEM_CONFIG_SECTION_score_bonus,
  META_PROBLEM_CONFIG_SECTION_open_tests,
  META_PROBLEM_CONFIG_SECTION_final_open_tests,
  META_PROBLEM_CONFIG_SECTION_extid,
  META_PROBLEM_CONFIG_SECTION_revision,
  META_PROBLEM_CONFIG_SECTION_test_sets,
  META_PROBLEM_CONFIG_SECTION_date_penalty,
  META_PROBLEM_CONFIG_SECTION_group_start_date,
  META_PROBLEM_CONFIG_SECTION_group_deadline,
  META_PROBLEM_CONFIG_SECTION_disable_language,
  META_PROBLEM_CONFIG_SECTION_enable_language,
  META_PROBLEM_CONFIG_SECTION_require,
  META_PROBLEM_CONFIG_SECTION_lang_time_adj,
  META_PROBLEM_CONFIG_SECTION_lang_time_adj_millis,
  META_PROBLEM_CONFIG_SECTION_personal_deadline,
  META_PROBLEM_CONFIG_SECTION_score_view,
  META_PROBLEM_CONFIG_SECTION_score_view_text,
  META_PROBLEM_CONFIG_SECTION_lang_compiler_env,
  META_PROBLEM_CONFIG_SECTION_checker_env,
  META_PROBLEM_CONFIG_SECTION_valuer_env,
  META_PROBLEM_CONFIG_SECTION_interactor_env,
  META_PROBLEM_CONFIG_SECTION_style_checker_env,
  META_PROBLEM_CONFIG_SECTION_test_checker_env,
  META_PROBLEM_CONFIG_SECTION_init_env,

  META_PROBLEM_CONFIG_SECTION_LAST_FIELD,
};

struct problem_config_section;

int meta_problem_config_section_get_type(int tag);
size_t meta_problem_config_section_get_size(int tag);
const char *meta_problem_config_section_get_name(int tag);
const void *meta_problem_config_section_get_ptr(const struct problem_config_section *ptr, int tag);
void *meta_problem_config_section_get_ptr_nc(struct problem_config_section *ptr, int tag);
int meta_problem_config_section_lookup_field(const char *name);

struct meta_methods;
extern const struct meta_methods meta_problem_config_section_methods;

#endif

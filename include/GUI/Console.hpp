#ifndef UE4SS_GUI_CONSOLE_HPP
#define UE4SS_GUI_CONSOLE_HPP

#include <vector>
#include <string>
#include <mutex>

#include <DynamicOutput/OutputDevice.hpp>
#include <imgui.h>
#include <TextEditor.h>

using namespace RC;

namespace RC::GUI
{
    class Console
    {
    private:
        char m_input_buffer[256]{};
        std::vector<std::string> m_lines{};
        ImGuiTextFilter m_filter{};
        float m_previous_max_scroll_y{};
        float m_current_console_output_width{};
        std::mutex m_lines_mutex{};
        TextEditor m_text_editor{};
        TextEditor::Breakpoints  m_breakpoints{};
        const size_t m_maximum_num_lines{50000};

    public:
        Console()
        {
            m_text_editor.SetConsoleMode(true);
            m_text_editor.SetColorizerEnable(false);
            m_text_editor.SetLanguageDefinition(GetLanguageDefinitionNone());
            m_text_editor.SetPalette(GetPalette());
            m_text_editor.GetErrorMarkers().emplace(6, "Test error");
            m_breakpoints.emplace(5);
            m_text_editor.SetBreakpoints(m_breakpoints);
            m_text_editor.SetTextFilter(&m_filter);
            m_text_editor.GetLineColorMarkers().emplace(4, std::pair{ImColor(148, 36, 20, 255), ImColor(255, 255, 255, 255)});
        }

    private:
        auto GetLanguageDefinitionNone() -> const TextEditor::LanguageDefinition&;
        auto GetPalette() const -> const TextEditor::Palette&;

    public:
        auto render() -> void;
        auto render_search_box() -> void;
        auto add_line(const std::string&, LogLevel::LogLevel) -> void;
        auto add_line(const std::wstring&, LogLevel::LogLevel) -> void;
    };
}

#endif //UE4SS_GUI_CONSOLE_HPP

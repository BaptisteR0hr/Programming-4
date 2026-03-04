#include "TrashTheCacheComponent.h"
#include <chrono>
#include <numeric>
#include <algorithm>
#include <imgui.h>

void dae::TrashTheCacheComponent::RenderImGui() {
    // --- OEFENING 1 ---
    ImGui::Begin("Exercise 1");
    ImGui::InputInt("# samples", &m_IntSamples);
    if (ImGui::Button("Trash the cache")) RunIntBenchmark(m_IntSamples);

    if (!m_IntResults.empty()) {
        ImGui::PlotLines("Int Results", m_IntResults.data(), static_cast<int>(m_IntResults.size()), 0, nullptr, 0.0f, 100.0f, ImVec2(0, 80));
    }
    ImGui::End();

    // --- OEFENING 2 ---
    ImGui::Begin("Exercise 2");
    ImGui::InputInt("# samples", &m_GameObjectSamples);

    if (ImGui::Button("Trash the cache with GameObject3D")) RunGameObjectBenchmark(m_GameObjectSamples);
    if (!m_GameObjectResults.empty()) {
        ImGui::PlotLines("Obj3D Results", m_GameObjectResults.data(), static_cast<int>(m_GameObjectResults.size()), 0, nullptr, 0.0f, 500.0f, ImVec2(0, 80));
    }

    if (ImGui::Button("Trash the cache with GameObject3DAlt")) RunGameObjectAltBenchmark(m_GameObjectSamples);
    if (!m_GameObjectAltResults.empty()) {
        ImGui::PlotLines("Alt Results", m_GameObjectAltResults.data(), static_cast<int>(m_GameObjectAltResults.size()), 0, nullptr, 0.0f, 500.0f, ImVec2(0, 80));
    }
    ImGui::End();
}

void dae::TrashTheCacheComponent::RunIntBenchmark(int samples) {
    const size_t bufferSize = 1 << 26;
    auto* buffer = new int[bufferSize];
    m_IntResults.clear();

    for (int step = 1; step <= 1024; step *= 2) {
        std::vector<float> timings;
        for (int s = 0; s < samples; ++s) {
            auto start = std::chrono::high_resolution_clock::now();
            for (size_t i = 0; i < bufferSize; i += step) buffer[i] *= 2;
            auto end = std::chrono::high_resolution_clock::now();
            timings.push_back(static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()));
        }
        std::sort(timings.begin(), timings.end());
        float avg = std::accumulate(timings.begin() + 1, timings.end() - 1, 0.0f) / (samples - 2);
        m_IntResults.push_back(avg);
    }
    delete[] buffer;
}

void dae::TrashTheCacheComponent::RunGameObjectBenchmark(int samples) {
    const size_t bufferSize = 1 << 22;
    auto* buffer = new GameObject3D[bufferSize];
    m_GameObjectResults.clear();

    for (int step = 1; step <= 1024; step *= 2) {
        std::vector<float> timings;
        for (int s = 0; s < samples; ++s) {
            auto start = std::chrono::high_resolution_clock::now();
            for (size_t i = 0; i < bufferSize; i += step) buffer[i].ID *= 2;
            auto end = std::chrono::high_resolution_clock::now();
            timings.push_back(static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()));
        }
        std::sort(timings.begin(), timings.end());
        float avg = std::accumulate(timings.begin() + 1, timings.end() - 1, 0.0f) / (samples - 2);
        m_GameObjectResults.push_back(avg);
    }
    delete[] buffer;
}

void dae::TrashTheCacheComponent::RunGameObjectAltBenchmark(int samples) {
    const size_t bufferSize = 1 << 22;
    auto* buffer = new GameObject3DAlt[bufferSize];
    m_GameObjectAltResults.clear();

    for (int step = 1; step <= 1024; step *= 2) {
        std::vector<float> timings;
        for (int s = 0; s < samples; ++s) {
            auto start = std::chrono::high_resolution_clock::now();
            for (size_t i = 0; i < bufferSize; i += step) buffer[i].ID *= 2;
            auto end = std::chrono::high_resolution_clock::now();
            timings.push_back(static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()));
        }
        std::sort(timings.begin(), timings.end());
        float avg = std::accumulate(timings.begin() + 1, timings.end() - 1, 0.0f) / (samples - 2);
        m_GameObjectAltResults.push_back(avg);
    }
    delete[] buffer;
}